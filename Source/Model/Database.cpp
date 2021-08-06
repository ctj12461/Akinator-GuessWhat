#include "Database.h"

#include <fstream>

using namespace std;

namespace Model {

/**
 * 构造函数
 * @date  2021-08-03
 */
DatabaseController::DatabaseController(string name) {
    if (name.size() != 0)
        open(name);
}

/**
 * 析构函数
 * @date  2021-08-03
 */
DatabaseController::~DatabaseController() {
    close();
}

/**
 * 打开指定名字的数据库，读取基本信息
 * @param name       数据库名称
 * @date  2021-08-03
 */
void DatabaseController::open(string name) {
    string headerName = getFileName(name, name, "gwdb-header");
    ifstream ifs(headerName);
    ifs >> attribute.name;
    ifs >> attribute.total;
    ifs >> attribute.blockTotal;
    ifs.close();
}

/**
 * 保持并关闭数据库
 * @date  2021-08-03
 */
void DatabaseController::close() {
    string headerName = getFileName(attribute.name, attribute.name, "gwdb-header");
    ofstream ofs(headerName);
    ofs << attribute.name << endl;
    ofs << attribute.total << endl;
    ofs << attribute.blockTotal << endl;
    ofs.close();
}

/**
 * 获取数据库属性
 * @return 属性
 * @date   2021-08-03
 */
DatabaseAttribute DatabaseController::getAttribute() const {
    return attribute;
}

/**
 * 获取 UUID = id 的块的数据
 * @param  id         块 UUID
 * @return            数据
 * @date   2021-08-03
 */
DatabaseBlock DatabaseController::getBlock(UuidType id) const {
    string dataName = getFileName(attribute.name, to_string(id), "gwdb-data");
    string buf;
    DatabaseBlock block;
    ifstream ifs(dataName);
    while (!ifs.eof()) {
        getline(ifs, buf, '\n');
        if (buf.size() == 0)
            break;
        block.data.push_back(buf);
    }
    block.setUuid(id);
    ifs.close();
    return block;
}

/**
 * 设置/更新数据库属性
 * @param attr       更新的属性
 * @date  2021-08-03
 */
void DatabaseController::setAttribute(DatabaseAttribute attr) {
    attribute = attr;
}

/**
 * 将 UUID = id 的块的数据写入数据库
 * @param id         UUID
 * @param block      数据
 * @date  2021-08-03
 */
void DatabaseController::setBlock(UuidType id, DatabaseBlock block) {
    string dataName = getFileName(attribute.name, to_string(id), "gwdb-data");
    ofstream ofs(dataName);
    for (string buf : block.data)
        ofs << buf << endl;
    ofs.close();
}

/**
 * 返回带路径文件名 (dir/name.prefix)
 * @param  dir        目录名
 * @param  name       文件名
 * @param  prefix     后缀
 * @return            处理后的文件名
 * @date   2021-08-06
 */
string DatabaseController::getFileName(string dir, string name, string prefix) const {
    return dir + string("/") + name + string(".") + prefix;
}

}
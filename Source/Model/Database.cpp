#include "Database.h"

#include <fstream>

using namespace std;

namespace Model {

/**
 * 构造函数
 * @date  2021-08-03
 */
DatabaseController::DatabaseController() {

}

/**
 * 析构函数
 * @date  2021-08-03
 */
DatabaseController::~DatabaseController() {

}

/**
 * 打开指定名字的数据库，读取基本信息
 * @param name       数据库名称
 * @date  2021-08-03
 */
void DatabaseController::open(string name) {
	string headerName = name + string(".gw-header");
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
	string headerName = attribute.name + string(".gw-header");
	ofstream ofs(headerName);
	ofs << attribute.name;
	ofs << attribute.total;
	ofs << attribute.blockTotal;
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
	string dataName = to_string(id) + string(".gw-data");
	string buf;
	DatabaseBlock block;
	ifstream ifs(dataName);
	while (true) {
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
	string dataName = to_string(id) + string(".gw-data");
	ofstream ofs(dataName);
	for (string buf : blocks.data)
		ofs << buf << endl;
	ofs.close();
}

}
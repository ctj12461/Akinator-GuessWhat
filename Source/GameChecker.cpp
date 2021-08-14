#include "GameChecker.h"

#include <fstream>

using namespace std;

namespace Controller {

GameChecker::GameChecker() {

}

GameChecker::~GameChecker() {

}

/**
 * 从配置文件中获取数据库名字，如果没有就按默认创建一个
 * @return [description]
 * @date   2021-08-14
 */
string GameChecker::getName() {
    ifstream ifs("GuessWhat.config");
    string name;
    getline(ifs, name, '\n');
    ifs.close();

    /** 如果没有配置过 */
    if (name.size() == 0) {
        makeDefaultConfig();
        ifs.open("GuessWhat.config");
        getline(ifs, name, '\n');
        ifs.close();
    }

    return name;
}

/**
 * 按默认创建一个配置文件和数据库
 * @date 2021-08-14
 */
void GameChecker::makeDefaultConfig() {
    /** 创建配置文件 */
    ofstream ofs("GuessWhat.config");
    ofs << "DefaultDatabase" << endl;
    ofs.close();
    
    /** 创建数据库属性文件 */
    ofs.open("DefaultDatabase/DefaultDatabase.gwdb-header");
    ofs << "DefaultDatabase" << endl;
    ofs << "3" << endl;
    ofs << "1" << endl;
    ofs.close();

    /** 创建数据块文件 */
    ofs.open("DefaultDatabase/1.gwdb-data");
    ofs << "1 0 Query 2 3 Can he or she speak and think?" << endl;
    ofs << "2 1 Answer human" << endl;
    ofs << "3 1 Answer animal" << endl;
    ofs.close();
}

}
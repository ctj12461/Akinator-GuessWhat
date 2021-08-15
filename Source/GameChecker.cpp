#include "GameChecker.h"

#include <fstream>
#include <cstdlib>

using namespace std;

namespace Controller {

GameChecker::GameChecker() {

}

GameChecker::~GameChecker() {

}

/**
 * 从配置文件中获取数据库名字，如果没有就按默认创建一个
 * @return 数据库名字
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
    
    system("mkdir DefaultDatabase");
    /** 创建数据库属性文件 */
    ofs.open("DefaultDatabase/DefaultDatabase.gwdb-header");
    ofs << "DefaultDatabase" << endl;
    ofs << "27" << endl;
    ofs << "1" << endl;
    ofs.close();

    /** 创建数据块文件 */
    ofs.open("DefaultDatabase/1.gwdb-data");
    ofs << "1 0 Query 4 3 Can he or she speak and think?" << endl;
    ofs << "2 8 Answer yourself" << endl;
    ofs << "3 1 Answer animal" << endl;
    ofs << "4 1 Query 22 8 Has that person ever written a program?" << endl;
    ofs << "5 22 Answer Linus Torvalds" << endl;
    ofs << "6 24 Query 23 7 Has that person created this guessing game?" << endl;
    ofs << "7 6 Answer Notch" << endl;
    ofs << "8 4 Query 10 2 Is that person very famous?" << endl;
    ofs << "9 14 Answer Ma Baoguo" << endl;
    ofs << "10 8 Query 12 14 Did that person open a live channel?" << endl;
    ofs << "11 20 Answer Lu Benwei" << endl;
    ofs << "12 10 Query 13 20 Is that person considered as the Mikado (the emperor of Japan)?" << endl;
    ofs << "13 12 Answer Sun Xiaochuan" << endl;
    ofs << "14 10 Query 16 9 Is that person a singer?" << endl;
    ofs << "15 16 Answer Rick Astley" << endl;
    ofs << "16 14 Query 18 15 Is that person a Chinese singer?" << endl;
    ofs << "17 18 Answer Wu Yifan" << endl;
    ofs << "18 16 Query 19 17 Can that person sing, dance, rap and play bastetball?" << endl;
    ofs << "19 18 Answer Cai Xukun" << endl;
    ofs << "20 12 Query 21 11 Does that person often play CS:GO?" << endl;
    ofs << "21 20 Answer Qiezi" << endl;
    ofs << "22 4 Query 5 24 Has that person written an OS?" << endl;
    ofs << "23 6 Answer Justin Chen (ctj12461)" << endl;
    ofs << "24 22 Query 6 25 Has that person created a game?" << endl;
    ofs << "25 24 Query 26 27 Has that person invented a programming language?" << endl;
    ofs << "26 25 Answer Dennis Ritchie" << endl;
    ofs << "27 25 Answer Richard Stallman" << endl;
    ofs.close();
}

}
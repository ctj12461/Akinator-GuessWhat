#include <iostream>
#include <cassert>
#include <string>

#include "../Database.h"
#include "../Definition.h"

using namespace std;
using namespace Model;

DatabaseController dbc;

int main() {
    /** 测试数据库 IO */
    /** 打开数据库 TestDatabase */
    dbc.open("TestDatabase");

    /** 获取数据库属性 */
    DatabaseAttribute attr = dbc.getAttribute();
    assert(attr.name == "TestDatabase");
    assert(attr.total == 3);
    assert(attr.blockTotal == 1);

    /** 获取数据块 */
    DatabaseBlock block = dbc.getBlock(1);
    assert(block.getUuid() == 1);
    cout << "1" << endl;
    for (auto s : block.data)
        cout << s << endl;
    /** 更改属性 */
    attr.total = 5;
    dbc.setAttribute(attr);

    /** 更改数据 */
    block.data.clear();
    block.data.push_back("1 0 Query 2 3 1 - QueryNode 1");
    block.data.push_back("2 1 Answer 2 - AnswerNode 1 (Yes)");
    block.data.push_back("3 1 Query 4 5 3 - QueryNode 2");
    block.data.push_back("4 3 Answer 4 - QueryNode 2 (Yes)");
    block.data.push_back("5 3 Answer 5 - QueryNode 3 (No)");
    dbc.setBlock(1, block);

    /** 关闭数据库 */
    dbc.close();

    cout << "Test passed" << endl;
    return 0;
}
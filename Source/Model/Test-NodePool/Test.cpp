#include <iostream>
#include <string>
#include <cassert>
#include <vector>

#include "../Definition.h"
#include "../LogicalNode.h"
#include "../ExtendedNode.h"
#include "../Database.h"
#include "../NodePool.h"

using namespace std;
using namespace Model;

DatabaseController dbc;
NodePool pool;

vector<LogicalNode *> vec;

void add(LogicalNode *p) {
    vec.push_back(p);
}

void output() {
    for (LogicalNode *p : vec) {
        if (p == nullptr)
            continue;
        if (p->getType() == NodeEnum::Query) {
            QueryNode *qp = dynamic_cast<QueryNode *>(p);
            cout << "UUID = " << qp->getUuid() << ", ";
            cout << "Previous = " << qp->getPrevious() << ", ";
            cout << "YesBranch = " << qp->getBranch(BranchEnum::Yes) << ", ";
            cout << "NoBranch = " << qp->getBranch(BranchEnum::No) << endl;
            cout << "Text = " << qp->getText() << endl;
            cout << endl;
        } else {
            AnswerNode *ap = dynamic_cast<AnswerNode *>(p);
            cout << "UUID = " << ap->getUuid() << ", ";
            cout << "Previous = " << ap->getPrevious() << endl;
            cout << "Text = " << ap->getText() << endl;
            cout << endl;
        }
    }
}

int main() {
    /** 初始化 */
    dbc.open("TestDatabase");
    pool.setDatabaseController(&dbc);

    /** 加载结点数据 */
    pool.load(add, 1);
    output();
    cout << vec.size() << endl;
    assert(vec.size() == 3);

    /** 测试是否会重复加载 */
    pool.load(add, 2);
    assert(vec.size() == 3);

    /** 测试添加结点 */
    vec.push_back(pool.newQueryNode("New QueryNode"));
    vec.push_back(pool.newAnswerNode("New AnswerNode 1"));
    vec.push_back(pool.newAnswerNode("New AnswerNode 2"));
    dynamic_cast<QueryNode *>(vec[3])->setPrevious(0);
    dynamic_cast<QueryNode *>(vec[3])->setBranch(BranchEnum::Yes, 5);
    dynamic_cast<QueryNode *>(vec[3])->setBranch(BranchEnum::No, 6);
    dynamic_cast<AnswerNode *>(vec[4])->setPrevious(4);
    dynamic_cast<AnswerNode *>(vec[5])->setPrevious(4);
    pool.save();
    {
        DatabaseAttribute attr = dbc.getAttribute();
        assert(attr.total == 6);
    }

    /** 测试是否会创建新的块 */
    {
        for (int i = 1; i <= 1000; ++i)
            pool.newAnswerNode(to_string(i));
        pool.save();
        DatabaseAttribute attr = dbc.getAttribute();
        assert(attr.total == 1006);
        assert(attr.blockTotal == 2);
    }

    dbc.close();
    cout << "Test passed" << endl;
    return 0;
}
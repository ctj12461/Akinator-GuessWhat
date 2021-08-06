#include <iostream>
#include <cassert>
#include <string>

#include "../Definition.h"
#include "../LogicalNode.h"
#include "../ExtendedNode.h"

using namespace std;
using namespace Model;

int main() {
    /** 测试 LogicalNode 能不能被构造 */
    // LogicalNode node;
    /** 不注释无法通过编译 */

    /** 测试 QueryNode 和 AnswerNode 功能 */
    {
        QueryNode qn("QueryNode");
        AnswerNode an1("AnswerNode 1"), an2("AnswerNode 2");

        /** 测试获取 UUID */
        qn.setUuid(1);
        an1.setUuid(2);
        an2.setUuid(3);
        
        qn.setPrevious(0);
        qn.setBranch(BranchEnum::Yes, 2);
        qn.setBranch(BranchEnum::No, 3);

        an1.setPrevious(1);
        an2.setPrevious(1);

        assert(qn.getUuid() == 1);
        assert(an1.getUuid() == 2);
        assert(an2.getUuid() == 3);
        assert(qn.getBranch(BranchEnum::Yes) == 2);
        assert(qn.getBranch(BranchEnum::No) == 3);
        assert(an1.getPrevious() == 1);
        assert(an2.getPrevious() == 1);

        /** 测试获取文本 */
        assert(qn.getText() == "QueryNode");
        assert(an1.getText() == "AnswerNode 1");
        assert(an2.getText() == "AnswerNode 2");

        /** 测试获取类型 */
        assert(qn.getType() == NodeEnum::Query);
        assert(an1.getType() == NodeEnum::Answer);
        assert(an2.getType() == NodeEnum::Answer);
    }
    cout << "Test passed." << endl;
    return 0;
}
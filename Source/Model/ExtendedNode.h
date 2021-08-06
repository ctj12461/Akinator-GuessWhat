#ifndef EXTENDED_NODE
#define EXTENDED_NODE

#include "Definition.h"
#include "LogicalNode.h"

#include <string>

using namespace std;

namespace Model {

class LogicalNode;

class QueryNode : public LogicalNode {
public:
    QueryNode(string t = "");
    ~QueryNode() noexcept;

    UuidType getBranch(BranchEnum b) const noexcept;

    void setBranch(BranchEnum b, UuidType id) noexcept;
private:
    UuidType branch[2];
};

class AnswerNode : public LogicalNode {
public:
    AnswerNode(string t = "");
    ~AnswerNode() noexcept;
};

}

#endif
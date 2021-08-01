#ifndef EXTENDED_NODE
#define EXTENDED_NODE

namespace Model {

class LogicalNode;

class QueryNode : public LogicalNode {
public:
	enum class BranchEnum {
		No, Yes
	};

	QueryNode(string t = "");
	~QueryNode();

	UuidType getBranch(BranchEnum b) const noexcept;

	void setBranch(BranchEnum b, UuidType id) noexcept;
private:
	UuidType branch[2];
};

class AnswerNode : public LogicalNode {
public:
	AnswerNode(string t = "");
	~AnswerNode();
};

}

#endif
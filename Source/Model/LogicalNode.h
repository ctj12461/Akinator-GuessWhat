#ifndef LOGICAL_NODE
#define LOGICAL_NODE

namespace Model {

class LogicalNode {
public:
	using UuidType = unsigned long long;

	enum class NodeEnum {
		Query, Answer
	};
	
	LogicalNode(NodeEnum n, string t = "");
	~LogicalNode() noexcept;
	
	NodeEnum getType() const noexcept;
	string getText() const noexcept;
	UuidType getUuid() const noexcept;
	bool isEnd() const noexcept;
	
	void setText(string t) noexcept;
protected:
	NodeEnum type;
	string text;
	UuidType uuid;
};

}

#endif
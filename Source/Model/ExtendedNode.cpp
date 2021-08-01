#include "ExtendedNode.h"
#include "LogicalNode.h"

namespace Model {

/**
 * 默认/自定义构造函数
 * @param t          初始文本
 * @date  2021-08-01
 */
QueryNode::QueryNode(string t) : LogicalNode(NodeEnum::Query, t) {
	branch[0] = branch[1] = 0;
}

/**
 * 析构函数
 */
QueryNode::~QueryNode() {

}

/**
 * 获取某一个分支结点的UUID
 * @param  b          分支 (Yes/No)
 * @return            UUID
 * @date   2021-08-01
 */
UuidType QueryNode::getBranch(BranchEnum b) const noexcept {
	return branch[static_cast<int>(b)];
}

/**
 * 设置某一个分支对应的结点 UUID
 * @param b          分支 (Yes/No)
 * @param id         UUID
 * @date  2021-08-01
 */
void QueryNode::setBranch(BranchEnum b, UuidType id) noexcept {
	branch[static_cast<int>(b)] = id;
}

/**
 * 默认/自定义构造函数
 * @param t          初始文本
 * @date  2021-08-01
 */
AnswerNode::AnswerNode(string t = "") : LogicalNode(NodeEnum::Answer, t) {

}

/**
 * 析构函数
 */
AnswerNode::~AnswerNode() {

}

}
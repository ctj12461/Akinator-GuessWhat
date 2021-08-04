#include "LogicalNode.h"

#include <string>

using namespace std;

namespace Model {

/**
 * 默认/自定义构造函数
 * @param n          当前结点类型
 * @param t          初始文本
 * @date  2021-08-01
 */
LogicalNode::LogicalNode(NodeEnum n, string t) noexcept 
    : uuid(LogicalNode::null) {
	type = n;
	text = t;
}

/**
 * 析构函数
 * @date  2021-08-01
 */
LogicalNode::~LogicalNode() noexcept {
	
}

/**
 * 返回当前结点的类型 (Quer	y/Answer)
 * @return 当前结点的类型
 * @date   2021-08-01
 */
NodeEnum LogicalNode::getType() const noexcept {
	return type;
}

/**
 * 返回当前结点的文本 (询问文本/答案)
 * @return 文本
 * @date   2021-08-01
 */
string LogicalNode::getText() const noexcept {
	return text;
}

/**
 * 返回当前结点的UUID
 * @return UUID
 * @date   2021-08-01
 */
UuidType LogicalNode::getUuid() const noexcept {
	return uuid;
}

/**
 * 判断当前结点是不是终点，即 Answer 结点
 * @return 判断结果
 * @date   2021-08-01
 */
bool LogicalNode::isEnd() const noexcept {
	return type == NodeEnum::Answer;
}

/**
 * 返回网络中的前驱结点
 * @return [description]
 * @date   2021-08-01
 */
UuidType LogicalNode::getPrevious() const noexcept {
    return previous;
}

/**
 * 设置当前结点的文本
 * @param t          要设置的文本
 * @date  2021-08-01
 */
void LogicalNode::setText(string t) noexcept {
	text = t;
}

/**
 * 设置当前结点的UUID
 * @date 2021-08-01
 */
void LogicalNode::setUuid(UuidType id) noexcept {
    uuid = id;
}

/**
 * 设置网络中的前驱结点
 * @param  id         前驱结点的 UUID
 * @date   2021-08-01
 */
void LogicalNode::setPrevious(UuidType id) noexcept {
    previous = id;
}

}
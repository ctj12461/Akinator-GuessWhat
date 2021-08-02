#ifndef DEFINATION
#define DEFINATION

/**
 * 结点的文本数据格式：
 * 1. QueryNode
 * [UUID] [PreviousUUID] Query [YesBranchUUID] [NoBranchUUID] [Text]
 * 2. AnswerNode
 * [UUID] [PreviousUUID] Answer [Text]
 */

using UuidType = unsigned long long;

enum class NodeEnum {
	Query, Answer
};

enum class BranchEnum {
	No, Yes
};

#endif
#ifndef DEFINATION
#define DEFINATION

/**
 * 数据库格式
 * 1.基本信息
 * 储存在 [name].gw-header 里：
 * [name]
 * [total]
 * [blockTotal]
 * 2. 结点信息
 * 储存在 [blockID].gw-data 里
 */

/**
 * 结点的文本数据格式
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
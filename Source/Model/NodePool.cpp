#include "NodePool.h"
#include "LogicalNode.h"
#include "ExtendedNode.h"
#include "Database.h"

#include <sstream>
#include <vector>
#include <cmath>
#include <utility>
#include <string>
#include <unordered_map>
#include <functional>

using namespace std;

namespace Model {

/**
 * 构造函数，设置空指针
 * @date   2021-08-02
 */
DataBlock::DataBlock() : size(0) {
	for (int i = 0; i < DataBlock::BlockSize; ++i)
		nodes[i] = nullptr;
}

/**
 * 析构函数，释放内存
 * @date   2021-08-02
 */
DataBlock::~DataBlock() {
	for (int i = 0; i < DataBlock::BlockSize; ++i)
		if (nodes[i] != nullptr)
			delete nodes[i];
}

/**
 * 根据文本数据序列化出结点，数据格式见 Definition.h
 * @return 储存文本数据的 vector<string>
 * @date   2021-08-02
 */
vector<string> DataBlock::serialize() const {
	string space(" ");
	vector<string> res;

	for (UuidType i = 0; i < size; ++i) {
		LogicalNode *p = nodes[i];
		if (p == nullptr)
			continue;

		string s("");
		s += to_string(p->getUuid()) + space;
		s += to_string(p->getPrevious()) + space;
		/** 判断是 Query 还是 Answer 结点 */
		if (p->getType() == NodeEnum::Query) {
			QueryNode *qp = dynamic_cast<QueryNode *>(p);
			s += string("Query") + space;
			s += to_string(qp->getBranch(BranchEnum::Yes)) + space;
			s += to_string(qp->getBranch(BranchEnum::No)) + space;
		} else {
			s += string("Answer") + space;
		}
		s += p->getText();

		res.push_back(s);
	}
	return res;
}

/**
 * 根据文本数据反序列化出结点，数据格式见 Definition.h
 * @param data       数据
 * @date  2021-08-02
 */
void DataBlock::deserialize(const vector<string> &data) {
	istringstream iss;
	string now, text;
	UuidType uuid = 0, prevUuid = 0, yesUuid = 0, noUuid = 0;
	LogicalNode *p = nullptr;

	for (string s : data) {
		iss.clear();
		iss.str(s);
		iss >> uuid >> prevUuid >> now;
		/** 判断是 Query 还是 Answer 结点 */
		if (now[0] == 'Q') {
			iss >> yesUuid >> noUuid;
			/** 去掉空格等字符 */
			while (isalnum(iss.peek()) == false)
				iss.get();
			getline(iss, text);
			QueryNode *qp = newQueryNode(text, uuid);
			qp->setPrevious(prevUuid);
			qp->setBranch(BranchEnum::Yes, yesUuid);
			qp->setBranch(BranchEnum::No, noUuid);
		} else {
			/** 去掉空格等字符 */
			while (isalnum(iss.peek()) == false)
				iss.get();
			getline(iss, text);
			AnswerNode *ap = newAnswerNode(text, uuid);
			ap->setPrevious(prevUuid);
		}
	}
}

/**
 * 分配一个 UUID = id 的 Query 结点，可以是文件中的，也
 * 可以是 NodePool 新创建的
 * @param  text       文本
 * @param  id         已知的 UUID
 * @return            指针
 * @date   2021-08-02
 */
QueryNode *DataBlock::newQueryNode(string text, UuidType id) {
	QueryNode *qp = new QueryNode(text);
	qp->setUuid(id);
	nodes[size++] = static_cast<LogicalNode *>(qp);
	return qp;
}

/**
 * 分配一个 UUID = id 的 Answer 结点，可以是文件中的，也
 * 可以是 NodePool 新创建的
 * @param  text       文本
 * @param  id         已知的 UUID
 * @return            指针
 * @date   2021-08-02
 */
AnswerNode *DataBlock::newAnswerNode(string text, UuidType id) {
	AnswerNode *ap = new AnswerNode(text);
	ap->setUuid(id);
	nodes[size++] = static_cast<LogicalNode *>(ap);
	return ap;
}

/**
 * 返回结点数大小
 * @return 大小
 * @date   2021-08-05
 */
UuidType DataBlock::getSize() const {
	return size;
}

/**
 * 返回指定下标的结点的指针
 * @param  id         下标
 * @return            指针
 * @date   2021-08-05
 */
LogicalNode *DataBlock::get(UuidType id) const {
	return nodes[id];
}

/**
 * 构造函数，初始化数据库的结点数 (不是已加载的结点数) 等信息
 * @date   2021-08-02
 */
NodePool::NodePool(DatabaseController *p) : database(p) {
	if (p == nullptr)
		return;
	DatabaseAttribute attr = database->getAttribute();
	total = attr.total;
	blockTotal = attr.blockTotal;
}

/**
 * 析构函数，将所有结点写入数据库，释放所有的块
 * @date   2021-08-02
 */
NodePool::~NodePool() {
	save();
	for (auto p : blocks) {
		if (p.second == nullptr)
			continue;
		delete p.second;
	}
	blocks.clear();
}

/**
 * 设置数据库控制器的指针
 * @param p          指针
 * @date  2021-08-02
 */
void NodePool::setDatabaseController(DatabaseController *p) {
	database = p;
	DatabaseAttribute attr = database->getAttribute();
	total = attr.total;
	blockTotal = attr.blockTotal;
}

/**
 * 新建一个 QueryNode，不是数据库中未加载的结点
 * @param  text       结点的文本
 * @return            新建结点的指针
 * @date   2021-08-02
 */
QueryNode *NodePool::newQueryNode(string text) {
	int uuid = total + 1;
	int blockid = getBlockId(uuid);
	/** 检查是否需要创建新的块 */
	if (blockid > blockTotal)
		newDataBlock();
	if (blocks.find(blockid) == blocks.end() || blocks[blockid] == nullptr)
		return nullptr;
	/** 新建结点 */
	QueryNode *qp = blocks[blockid]->newQueryNode(text, uuid);
	if (qp != nullptr)
		++total;
	return qp;
}

/**
 * 新建一个 AnswerNode，不是数据库中未加载的结点
 * @param  text       结点的文本
 * @return            新建结点的指针
 * @date   2021-08-02
 */
AnswerNode *NodePool::newAnswerNode(string text) {
	int uuid = total + 1;
	int blockid = getBlockId(uuid);
	/** 检查是否需要创建新的块 */
	if (blockid > blockTotal)
		newDataBlock();
	if (exist(blockid) == false)
		return nullptr;
	/** 新建结点 */
	AnswerNode *ap = blocks[blockid]->newAnswerNode(text, uuid);
	if (ap != nullptr)
		++total;
	return ap;
}

/**
 * 返回数据库控制器的指针
 * @return            指针
 * @date 2021-08-02
 */
DatabaseController *NodePool::getDatabaseController() const noexcept {
	return database;
}

/**
 * 从数据库中加载 UUID = id 的结点和同一个块的结点，不合法则
 * 直退出不做任何操作，并将它们用 f 添加
 * @param f          外部用于回调的函数，添加结点
 * @param id         要加载结点的 UUID
 * @date  2021-08-02
 */
void NodePool::load(function<void(LogicalNode *)> f, UuidType id) {
	int blockid = getBlockId(id);
	if (blockid > blockTotal)
		return;
	if (exist(blockid) == true)
		return;
	DatabaseBlock block = database->getBlock(blockid);
	DataBlock *p = new DataBlock;
	if (p == nullptr)
		return;
	blocks[blockid] = p;
	p->deserialize(block.data);
	for (UuidType i = 0; i < p->getSize(); ++i)
		f(p->get(i));
}

/**
 * 将结点信息写入数据库
 * @date 2021-08-06
 */
void NodePool::save() {
	for (auto p : blocks) {
		if (p.second == nullptr)
			continue;
		DatabaseBlock block(p.first, p.second->serialize());
		database->setBlock(p.first, block);
	}
	DatabaseAttribute attr = database->getAttribute();
	attr.total = total;
	attr.blockTotal = blockTotal;
	database->setAttribute(attr);
}

/**
 * 返回总结点数
 * @return 结点数
 * @date   2021-08-06
 */
UuidType NodePool::size() const noexcept {
	return total;
}

/**
 * 检查是否加载了 UUID = id 的块
 * @param  id         块的 UUID
 * @return            判断结果
 * @date   2021-08-02
 */
bool NodePool::exist(UuidType id) noexcept {
	return blocks.find(id) != blocks.end() && (blocks[id]) != nullptr;
}

/**
 * 辅助方法，根据 UUID 计算块的 UUID
 * @param  uuid       结点 UUID
 * @return            块 UUID
 * @date   2021-08-02
 */
UuidType NodePool::getBlockId(UuidType uuid) const noexcept {
	return static_cast<UuidType>(ceil(1.0 * uuid / DataBlock::BlockSize));
}

/**
 * 创建一个块
 * @return 新的块的 UUID
 * @date   2021-08-02
 */
UuidType NodePool::newDataBlock() {
	++blockTotal;
	DataBlock *p = new DataBlock;
	blocks[blockTotal] = p;
	return blockTotal;
}

}
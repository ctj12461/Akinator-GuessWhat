#ifndef NODEPOOL_H
#define NODEPOOL_H

#include "Definition.h"

#include <vector>
#include <string>
#include <unordered_map>
#include <functional>

using namespace std;

namespace Model {

class LogicalNode;
class QueryNode;
class AnswerNode;

class DatabaseController;

class DataBlock {
public:
	static constexpr UuidType BlockSize = 1000;

	DataBlock();
	~DataBlock();

	vector<string> serialize() const;
	void deserialize(const vector<string> &data);

	QueryNode *newQueryNode(string text, UuidType id);
	AnswerNode *newAnswerNode(string text, UuidType id);

	UuidType getSize() const;
	LogicalNode *get(UuidType id) const;
private:
	LogicalNode *nodes[BlockSize];
	UuidType size;
};

class NodePool {
public:
	NodePool(DatabaseController *p = nullptr);
	~NodePool();

	void setDatabaseController(DatabaseController *p);
	QueryNode *newQueryNode(string text);
	AnswerNode *newAnswerNode(string text);

	DatabaseController *getDatabaseController() const noexcept;
	void load(function<void(LogicalNode *)> f, UuidType id);
	void save();
private:
	unordered_map<UuidType, DataBlock *> blocks;
	UuidType total;
	UuidType blockTotal;
	DatabaseController *database;

	bool exist(UuidType uuid) noexcept;
	UuidType getBlockId(UuidType uuid) const noexcept;
	UuidType newDataBlock();
};

}

#endif
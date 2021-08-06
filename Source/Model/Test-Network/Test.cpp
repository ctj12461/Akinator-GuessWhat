#include <iostream>
#include <string>
#include <vector>
#include <cassert>

#include "../Definition.h"
#include "../Network.h"
#include "../NodePool.h"
#include "../Database.h"
#include "../LogicalNode.h"
#include "../ExtendedNode.h"

using namespace std;
using namespace Model;

DatabaseController dbc;
NodePool pool;
Network network;

int main() {
	/** 初始化 */
	dbc.open("TestDatabase");
	pool.setDatabaseController(&dbc);
	network.setNodePool(&pool);

	/** 测试结点信息是否正确 */
	assert(network.size() == 3);

	/** 测试网络上的指针的移动 */
	assert(network.getText() == "1 - QueryNode");
	assert(network.getCurrentUuid() == 1);
	assert(network.isEnd() == false);
	network.goNext(BranchEnum::Yes);
	assert(network.getText() == "2 - AnswerNode (Yes)");
	assert(network.getCurrentUuid() == 2);
	assert(network.isEnd() == true);
	network.goPrevious();
	network.goNext(BranchEnum::No);
	assert(network.getText() == "3 - AnswerNode (No)");
	assert(network.getCurrentUuid() == 3);
	assert(network.isEnd() == true);
	network.reset();
	assert(network.getCurrentUuid() == 1);

	/** 测试扩展结点 */
	network.goNext(BranchEnum::Yes);
	network.extend("New QueryNode 1", "New AnswerNode (No)", BranchEnum::No);
	network.reset();
	network.goNext(BranchEnum::No);
	network.extend("New QueryNode 2", "New AnswerNode (Yes)", BranchEnum::Yes);
	network.reset();
	
	assert(network.size() == 7);

	network.goNext(BranchEnum::Yes);
	assert(network.getText() == "New QueryNode 1");
	network.goNext(BranchEnum::No);
	assert(network.getText() == "New AnswerNode (No)");

	network.reset();

	network.goNext(BranchEnum::No);
	assert(network.getText() == "New QueryNode 2");
	network.goNext(BranchEnum::Yes);
	assert(network.getText() == "New AnswerNode (Yes)");
	
	cout << "Test passed." << endl;
	return 0;
}
#ifndef NETWORK_H
#define NETWORK_H

#include "Definition.h"

#include <unordered_map>
#include <string>

using namespace std;

namespace Model {

class NodePool;
class LogicalNode;

class Network {
public:
    Network(NodePool *p = nullptr);
    ~Network() noexcept;
    
    string getText();
    bool isValid();
    bool isEnd();
    UuidType getCurrentUuid() const;
    UuidType size() const;

    void setCurrentUuid(UuidType id);
    void setNodePool(NodePool *p);
    void goNext(BranchEnum b);
    void goPrevious();
    void reset();
    void addNode(LogicalNode *p);
    void extend(string query, string answer, BranchEnum which);
private:
    static constexpr UuidType origin = 1;
    UuidType current;
    unordered_map<UuidType, LogicalNode *> nodes;
    NodePool *pool;

    BranchEnum other(BranchEnum b) const noexcept;
    UuidType next(UuidType now, BranchEnum b);
    LogicalNode *deref(UuidType id);
    bool exist(UuidType id) const;
    void load(UuidType id);
};

}

#endif
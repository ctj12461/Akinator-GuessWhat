#include "Network.h"
#include "LogicalNode.h"
#include "ExtendedNode.h"
#include "NodePool.h"

#include <unordered_map>
#include <functional>
#include <string>

using namespace std;

namespace Model {

/**
 * 构造函数
 * @param tot        网络中的结点数
 * @param p          结点管理器的弱指针
 * @date  2021-08-01
 */
Network::Network(NodePool *p) : pool(p), current(origin) {

}

/**
 * 析构函数
 * @date  2021-08-01
 */
Network::~Network() noexcept {

}

/**
 * 获取当前结点的文本，即 UUID = current 的结点的文本，
 * 如果不合法返回空字符串
 * @return 文本
 * @date   2021-08-01
 */
string Network::getText() {
    if (isVaild() == false)
        return string("");
    return deref(current)->getText();
}

/**
 * 判断当前结点是否合法，即是否存在该结点
 * @return 判断结果
 * @date   2021-08-01
 */
bool Network::isVaild() {
    if (current == LogicalNode::null)
        return false;
    return deref(current) != nullptr;
}

/**
 * 判断当前结点是否是 Answer 结点，如果不合法返回 true
 * @return 判断结果
 * @date   2021-08-01
 */
bool Network::isEnd() {
    if (isVaild() == false)
        return true;
    return deref(current)->isEnd();
}

/**
 * 获取当前结点的 UUID
 * @return UUID
 * @date   2021-08-01
 */
UuidType Network::getCurrentUuid() const {
    return current;
}

/**
 * 获取网络中的结点数
 * @return 结点个数
 * @date   2021-08-01
 */
UuidType Network::size() const {
    if (pool == nullptr)
        return 0;
    return pool->size();
}

/**
 * 设置当前结点为 UUID = id 的结点
 * @param id         要设置的结点的 UUID
 * @date  2021-08-01
 */
void Network::setCurrentUuid(UuidType id) {
    current = id;
}

/**
 * 设置结点管理器
 * @param p          结点管理器的指针
 * @date  2021-08-01
 */
void Network::setNodePool(NodePool *p) {
    pool = p;
    if (p == nullptr)
        return;
    nodes.clear();
    current = Network::origin;
}

/**
 * 移动到指定的分支 (Yes/No)，如果是 Answer 结点则不做改动
 * @param b          分支 (Yes/No)
 * @date  2021-08-01
 */
void Network::goNext(BranchEnum b) {
    if (isVaild() == false)
        return;
    if (deref(current)->getType() == NodeEnum::Answer)
        return;
    current = dynamic_cast<QueryNode *>(deref(current))->getBranch(b);
}

/**
 * 移动到前驱结点
 * @param b          分支 (Yes/No)
 * @date  2021-08-06
 */
void Network::goPrevious() {
    if (isVaild() == false)
        return;
    if (deref(current)->getPrevious() == LogicalNode::null)
        return;
    current = deref(current)->getPrevious();
}

/**
 * 设置当前结点为初始结点
 * @date 2021-08-01
 */
void Network::reset() {
    current = origin;
}

/**
 * 添加一个结点
 * @param p          结点的弱指针
 * @date  2021-08-01
 */
void Network::addNode(LogicalNode *p) {
    if (p == nullptr)
        return;
    nodes[p->getUuid()] = p;
}

/**
 * 对 Answer 结点进行扩展，变为一个 Query 结点，新的 Answer 结点
 * 和原来的 Answer 结点，使推测的答案更细化
 * @param query      Query 结点的文本
 * @param answer     新 Answer 结点的文本
 * @param which      新的 Answer 结点是哪个分支 (Yes/No)
 * @date  2021-08-01
 */
void Network::extend(string query, string answer, BranchEnum which) {
    if (pool == nullptr)
        return;
    AnswerNode *p = dynamic_cast<AnswerNode *>(deref(current));
    if (p == nullptr)
        return;
    /** 获取新结点 */
    QueryNode *qp = pool->newQueryNode(query);
    AnswerNode *ap = pool->newAnswerNode(answer);
    addNode(qp);
    addNode(ap);
    /** 设置 qp 前驱后继，p & ap 的前驱 */
    qp->setPrevious(p->getPrevious());
    p->setPrevious(qp->getUuid());
    ap->setPrevious(qp->getUuid());
    qp->setBranch(which, ap->getUuid());
    qp->setBranch(other(which), p->getUuid());
    /** 设置 qp 前驱的后继 */
    if (qp->getPrevious() == LogicalNode::null)
        return;
    QueryNode *pp = dynamic_cast<QueryNode *>(deref(qp->getPrevious()));
    if (pp->getBranch(BranchEnum::Yes) == current)
        pp->setBranch(BranchEnum::Yes, qp->getUuid());
    else
        pp->setBranch(BranchEnum::No, qp->getUuid());
}

/**
 * 返回分支 (Yes/No) 的另一半，即 Yes -> No，No -> Yes
 * @param  b          分支
 * @return            另一半的分支
 * @date   2021-08-01
 */
BranchEnum Network::other(BranchEnum b) const noexcept {
    if (b == BranchEnum::Yes)
        return BranchEnum::No;
    else
        return BranchEnum::Yes;
}

/**
 * 返回指向指定的分支 (Yes/No) 的结点，如果是 Answer 结点或
 * 不合法则返回 LogicalNode::null
 * @param  now        UUID = now 的结点
 * @param  b          分支
 * @return            指定的分支 (Yes/No) 的结点的 UUID
 * @date   2021-08-01
 */
UuidType Network::next(UuidType now, BranchEnum b) {
    if (now == LogicalNode::null)
        return LogicalNode::null;
    if (deref(now) == nullptr)
        return LogicalNode::null;
    if (deref(now)->getType() == NodeEnum::Answer)
        return LogicalNode::null;
    return dynamic_cast<QueryNode *>(deref(now))->getBranch(b);
}

/**
 * 根据 UUID 返回结点的指针，如果不合法返回 nullptr
 * @param  id         指定结点的 UUID
 * @return            指定结点的指针
 * @date   2021-08-01
 */
LogicalNode *Network::deref(UuidType id) {
    if (id == LogicalNode::null)
        return nullptr;
    if (exist(id) == false)
        load(id);
    /** 从文件中加载后再次检查是否存在 */
    if (exist(id) == false)
        return nullptr;
    return nodes[id];
}

/**
 * 检查 UUID = id 的结点是否已经加载
 * @param  id         UUID
 * @return            判断结果
 * @date   2021-08-02
 */
bool Network::exist(UuidType id) const {
    return nodes.find(id) != nodes.end();
}

/**
 * 通过 NodePool 加载指定 UUID 的结点，并加载 UUID 
 * 与其在同一个块的结点。将 Network::addNode() 传给
 * pool，再回调方法添加结点
 * @param id         UUID
 * @date  2021-08-02
 */
void Network::load(UuidType id) {
    using std::placeholders::_1;
    /** 添加回调方法 */
    pool->load(bind(&Network::addNode, this, _1), id);
}

}
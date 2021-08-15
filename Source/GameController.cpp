#include "GameController.h"
#include "./View/UserInterface.h"
#include "./Model/Definition.h"
#include "./Model/Network.h"
#include "./Model/NodePool.h"
#include "./Model/Database.h"

using namespace std;

namespace Controller {

/**
 * 构造对象
 * @date  2021-08-14
 */
GameController::GameController() {
    ui = new View::UserInterface;
    database = new Model::DatabaseController;
    pool = new Model::NodePool;
    network = new Model::Network;
}

/**
 * 释放对象
 * @date  2021-08-14
 */
GameController::~GameController() {
    delete ui;
    delete network;
    delete pool;
    delete database;
}


/**
 * 初始化，加载游戏数据，欢迎
 * @param name       数据库名称
 * @date  2021-08-14
 */
void GameController::init(string name) {
    /** 加载数据 */
    database->open(name);
    pool->setDatabaseController(database);
    network->setNodePool(pool);
    /** 欢迎界面 */
    ui->start();
    ui->introduce();
}

/**
 * 程序主循环，创建每一局游戏
 * @date 2021-08-14
 */
void GameController::loop() {
    while (true) {
        /** 新一局游戏 */
        game();
        /** 询问要不要再来一次 */
        View::MenuResult res = ui->again();
        if (res.item == "No"s)
            break;
    }
}

/**
 * 游戏退出
 * @date 2021-08-14
 */
void GameController::quit() {
    /** 退出界面 */
    ui->quit();
}

void GameController::game() {
    network->reset();
    /** 询问问题，一步步推测答案 */
    while (network->isEnd() == false) {
        /** 获得用户回答 */
        View::MenuResult res = ui->ask(network->getText());
        if (res.item == "Yes"s)
            network->goNext(Model::BranchEnum::Yes);
        else
            network->goNext(Model::BranchEnum::No);
    }
    /** 向玩家确认答案 */
    View::MenuResult res = ui->confirm(network->getText());
    if (res.item == "Yes"s) {
        ui->cheer();
    } else {
        /** 学习 */
        View::LearningResult res = ui->learn(network->getText());
        Model::BranchEnum branch;
        if (res.branch.item == "Yes"s)
            branch = Model::BranchEnum::Yes;
        else
            branch = Model::BranchEnum::No;
        network->extend(res.question, res.answer, branch);
    }
}

}
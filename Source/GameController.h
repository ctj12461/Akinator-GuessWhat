#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <string>

namespace View {

class UserInterface;

}

namespace Model {

class Network;
class NodePool;
class DatabaseController;

}

using namespace std;

namespace Controller {

class GameController {
public:
    GameController();
    ~GameController();

    void init(string name);
    void loop();
    void quit();
private:
    View::UserInterface *ui;
    Model::Network *network;
    Model::NodePool *pool;
    Model::DatabaseController *database;

    void game();
};

}

#endif
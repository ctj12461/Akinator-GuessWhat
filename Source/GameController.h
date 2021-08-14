#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <string>

class View::UserInterface;
class Model::Network;
class Model::NodePool;
class Model::DatabaseController;

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
#ifndef GAMECHECKER_H
#define GAMECHECKER_H

#include <string>

using namespace std;

namespace Controller {

class GameChecker {
public:
    GameChecker();
    ~GameChecker();
    
    string getName();
private:
    void makeDefaultConfig();
};

}

#endif
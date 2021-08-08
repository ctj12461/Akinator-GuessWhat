#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "Menu.h"

#include <string>

namespace View {

struct LearningResult {
    string question;
    string answer;
    MenuResult branch;
};

class UserInterface {
public:
    UserInterface();
    ~UserInterface();
    
    void start();
    MenuResult ask(string question);
    MenuResult confirm(string answer);
    void cheer();
    LearningResult learn(string answer);
    MenuResult again();
    void quit();
};

}

#endif
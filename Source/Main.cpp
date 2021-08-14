#include "GameChecker.h"
#include "GameController.h"

using namespace Controller;

GameChecker checker;
GameController controller;

int main() {
    controller.init(checker.getName());
    controller.loop();
    controller.quit();
    return 0;
}
#include "UserInterface.h"

#include <iostream>
#include <stirng>

using namespace std;

namespace View {

UserInterface::UserInterface() {

}

UserInterface::~UserInterface() {

}

/**
 * 绘制启动界面
 * @date 2021-08-07
 */
void UserInterface::start() {
    cout << R"(   ______                    _       ____          __ )" << endl
         << R"(  / ____/_  _____  _________| |     / / /_  ____ _/ /_)" << endl
         << R"( / / __/ / / / _ \/ ___/ ___/ | /| / / __ \/ __ `/ __/)" << endl
         << R"(/ /_/ / /_/ /  __(__  |__  )| |/ |/ / / / / /_/ / /_  )" << endl
         << R"(\____/\__,_/\___/____/____/ |__/|__/_/ /_/\__,_/\__/  )" << endl 
         << R"(                                                      )" << endl;
    cout << R"(           Welcome to Akinator:GuessWhat.             )" << endl;
    cout << R"(      Copyright (C) Justin Chen (aka ctj12461)        )" << endl;
    cout << endl;
}

/**
 * 询问一个问题，并返回 Yes 或 No
 * @param  question   问题文本
 * @return            输入的结果
 * @date   2021-08-07
 */
MenuResult UserInterface::ask(string question) {
    Menu menu;
    menu.addItem("Yes");
    menu.addItem("No");
    cout << question << endl;
    return menu.show();
}

/**
 * 确认正确答案是不是 answer
 * @param  answer     猜测的答案
 * @return            是不是正确
 * @date   2021-08-08
 */
MenuResult UserInterface::confirm(string answer) {
    Menu menu;
    menu.addItem("Yes");
    menu.addItem("No");
    cout << endl;
    cout << "Is who you think " + answer << "?" << endl;
    return menu.show();
}

/**
 * 答对时的表现
 * @date 2021-08-08
 */
void UesrInterface::cheer() {
    cout << "How smart I am." << endl;
}

/**
 * 答错后，学习
 * @param  answer     猜测的答案
 * @return            学习结果，由新问题，新答案和新答案对应新问题的结果组成
 * @date   2021-08-08
 */
LearningResult UserInterface::learn(string answer) {
    InputBox box;
    box.setText("Who is he or she?");
    string newAnswer = box.input();
    string askText = "Could you tell me a question which helps me recognize ";
    askText += newAnswer + " and " + answer + "?";
    box.setText(askText);
    string question = box.input();

    Menu menu;
    menu.addItem("Yes");
    menu.addItem("No");
    cout << "What's the answer if he or she is "s + newAnswer + "?" << endl;
    MenuResult res = menu.show();
    cout << "Thank you very much. I learn from you a lot." << endl;
    return {question, newAnswer, res};
}

/**
 * 询问是否要重新开始
 * @return 输入的结果
 * @date   2021-08-08
 */
MenuResult UserInterface::again() {
    cout << "Would you like to play again?" << endl;
    Menu menu;
    menu.addItem("Yes");
    menu.addItem("No");
    return menu.show();
}

/**
 * 退出界面
 * @date 2021-08-08
 */
void UserInterface::quit() {
    cout << "See you next time." << endl;
}

}
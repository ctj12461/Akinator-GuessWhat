#include "InputBox.h"

#include <iostream>
#include <string>

using namespace std;

namespace View {

/**
 * 构造函数，初始化询问文本
 * @param t          文本
 * @date  2021-08-07
 */
InputBox::InputBox(string t) : text(t) {

}

/**
 * 析构函数
 * @date  2021-08-07
 */
InputBox::~InputBox() {

}

/**
 * 设置输入框的文本
 * @param t          文本
 * @date  2021-08-07
 */
void InputBox::setText(string t) {
    text = t;
}

/**
 * 获取输入 (整行)
 * @return 输入的信息
 * @date   2021-08-07
 */
string InputBox::input() {
    cout << text << endl;
    cout << "> ";
    string in;
    bool first = true;
    do {
        getline(cin, in, '\n');
        if (in.size() == 0 && first == false) {
            cout << "Invalid input." << endl;
            cout << "> ";
        }
        first = false;
    } while (in.size() == 0);
    return in;
}

}
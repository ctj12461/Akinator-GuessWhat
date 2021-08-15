#include "Menu.h"

#include <string>
#include <iostream>
#include <iomanip>

namespace View {

Menu::Menu() {

}

Menu::~Menu() {

}

/**
 * 设置菜单的标题
 * @param ti         标题文本
 * @date  2021-08-07
 */
void Menu::setTitle(string ti) {
    title = ti;
}

/**
 * 添加选择项目
 * @param item       项目文本
 * @date  2021-08-07
 */
void Menu::addItem(string item) {
    items.push_back(item);
}

/**
 * 显示菜单并读取输入
 * @return 选择的项目编号
 * @date   2021-08-07
 */
MenuResult Menu::show() {
    if (title.size() != 0)
        cout << " [ " << title << " ]" << endl;
    for (int i = 0; i < items.size(); ++i) {
        string number = to_string(i + 1) + string(")");
        cout << " " << setw(4) << left << number << items[i] << endl;
    }
    cout << "Type a number to choose one item and press \"Enter\"." << endl;
    cout << "> ";
    int choice;
    do {
        while (isdigit(cin.peek()) == false)
            cin.get();
        cin >> choice;
        /** 检查输入是否合法 */
        if (choice > items.size() || choice < 1) {
            cout << "Invaild input." << endl;
            cout << "> ";
        }
    } while (choice > items.size() || choice < 1);
    return {choice, items[choice - 1]};
}

}
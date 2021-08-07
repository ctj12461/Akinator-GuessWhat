#include "Menu.h"

#include <string>
#include <iostream>
#include <iomanip>

namespace View {

Menu::Menu() {

}

Menu::~Menu() {

}

void Menu::setTitle(string ti) {
    title = ti;
}

void Menu::addItem(string item) {
    items.push_back(item);
}

int Menu::show() {
    cout << " # " << title << " #" << endl;
    for (int i = 0; i < items.size(); ++i)
        cout << " " << setw(4) << left << i + 1 << ") " << items[i] << endl;
    cout << "Type a number to choose one item and press \"Enter\".";
    int choice;
    cin >> choice;
    return choice;
}


}
#ifndef MENU_H
#define MENU_H

#include <string>
#include <vector>
#include <utility>

using namespace std;

namespace View {

struct MenuResult {
    int id;
    string item;
};

class Menu {
public:
    Menu();
    ~Menu();

    void setTitle(string ti);
    void addItem(string item);
    MenuResult show();
private:
    string title;
    vector<string> items;
};

}

#endif
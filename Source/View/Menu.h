#ifndef MENU
#define MENU

#include <string>

namespace View {

class Menu {
public:
    Menu();
    ~Menu();

    void setTitle(string ti);
    void addItem(string item);
    int show();
private:
    stirng title;
    vector<string> items;
};

}

#endif
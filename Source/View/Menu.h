#ifndef MENU
#define MENU

#include <string>
#include <vector>
#include <utility>

using namespace std;

namespace View {

class Menu {
public:
    Menu();
    ~Menu();

    void setTitle(string ti);
    void addItem(string item);
    pair<int, string> show();
private:
    string title;
    vector<string> items;
};

}

#endif
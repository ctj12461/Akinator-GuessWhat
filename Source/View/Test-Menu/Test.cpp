#include <iostream>
#include <string>

#include "../Menu.h"

using namespace std;
using namespace View;

Menu menu;

int main() {
    /** 初始化 */
    menu.setTitle("Menu Test");
    
    menu.addItem("Yes");
    menu.addItem("No");
    menu.addItem("I dont' know");
    menu.addItem("May be");
    menu.addItem("May not be");
    menu.addItem("Quit");

    /** 询问 */
    pair<int, string> res;
    do {
        res = menu.show();
        cout << "You chose " << res.first << " - " << res.second << endl;
    } while (res.second != "Quit");

    return 0;
}
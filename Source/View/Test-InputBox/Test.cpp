#include <iostream>
#include <string>

#include "../InputBox.h"

using namespace std;
using namespace View;

InputBox box;
string text;

int main() {
    /** 初始化 */
    box.setText("Type some text and I will repeat it. Type \"q\" to quit.");

    /** 复读 */
    do {
        text = box.input();
        if (text != "q"s)
            cout << text << endl;
    } while (text != "q"s);
    return 0;
}
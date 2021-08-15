#ifndef INPUTBOX_H
#define INPUTBOX_H

#include <string>

using namespace std;

namespace View {

class InputBox {
public:
    InputBox(string t = "");
    ~InputBox();

    void setText(string t);
    string input();
private:
    string text;
};

}

#endif
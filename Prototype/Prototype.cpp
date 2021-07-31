#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const string nullString = "@@null@@";

struct Node {
    string Text;
    int Left, Right;
    bool leaf() { return Left == 0 && Right == 0; }
};

const int MaxSize = 10000;
Node Tree[MaxSize]; int Total, Root;
bool wrong = false;

int create(string txt);
bool check();
bool getAnswer(int root);
void learn(int root);
void ask();
void run();
void serialize(int root, ofstream &fs);
void deserialize(int &root, ifstream &fs);
void save(string fname);
void load(string fname);

int main(int argc, const char *argv[]) {
    string name;
    cout << "Input a file name : ";
    cin >> name;
    load(name);
    run();
    save(name);
    return 0;
}

int create(string txt) {
    Tree[++Total] = { txt, 0, 0 };
    return Total;
}

bool check() {
    string input;
    cin >> input;
    if (toupper(input[0]) == 'Y') {
        return true;
    } else {
        return false;
    }
}

bool getAnswer(int root) {
    if (Tree[root].leaf() == false)
        cout << Tree[root].Text << " (yes or no)" << endl;
    else
        cout << "Are you a(n)" << Tree[root].Text << "? (yes or no)" << endl;
    return check();
}

void learn(int root) {
    string tmp = Tree[root].Text, name, question;
    cout << "Who are you?" << endl;
    cin >> name;
    cout << "Could you tell me a question which helps me recognize you and " << tmp << "?" << endl;
    cin.ignore(); getline(cin, question, '\n');
    cout << "Could you tell me the answer of the question if you\'re " << name << "? (yes or no)" << endl;
    bool answer = check();
    Tree[root].Text = question;
    if (answer == true) {
        Tree[root].Left = create(tmp);
        Tree[root].Right = create(name);
    } else {
        Tree[root].Left = create(name);
        Tree[root].Right = create(tmp);
    }
}

void ask() {
    int root = Root;
    if (root == 0)
        return;
    while(!Tree[root].leaf()){
        bool answer = getAnswer(root);
        if (answer == true) {
            root = Tree[root].Right;
        } else {
            root = Tree[root].Left;
        }
    }
    bool answer = getAnswer(root);
    if (answer == true) {
        cout << "I\'m so smart!!!" << endl;
    } else {
        wrong = true;
        learn(root);
    }
    cout << endl;
}

void run() {
    cout << "Hello!!!" << endl;
    cout << "Please answer my questions, and I try to guess what you are." << endl;
    do {
        ask();
        cout << "Do you want to play with me again? (yes or no)" << endl;
    } while(check());
    if (wrong)
        cout << "Thank you for teaching me a lot." << endl;
    else
        cout << "Goodbye!" << endl;
}

void serialize(int root, ofstream &fs) {
    if (root == 0) {
        fs << nullString << endl;
        return;
    }
    fs << Tree[root].Text << endl;
    serialize(Tree[root].Left, fs);
    serialize(Tree[root].Right, fs);
}

void deserialize(int &root, ifstream &fs) {
    string in;
    getline(fs, in, '\n');
    if (in == nullString)
        return;
    root = create(in);
    deserialize(Tree[root].Left, fs);
    deserialize(Tree[root].Right, fs);
}

void save(string fname) {
    ofstream fs(fname);
    serialize(Root, fs);
    fs.close();
}

void load(string fname) {
    ifstream fs(fname);
    deserialize(Root, fs);
    fs.close();
}

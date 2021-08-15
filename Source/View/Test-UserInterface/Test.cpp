#include <iostream>
#include <string>

#include "../UserInterface.h"

using namespace std;
using namespace View;

UserInterface ui;

int main() {
    /** 启动界面 */
    ui.start();

    /** 询问问题 */
    {
        MenuResult res = ui.ask("Can you speak?");
        cout << res.id << " " << res.item << endl;
    }

    /** 确认答案 */
    {
        MenuResult res = ui.confirm("ctj12461");
        cout << res.id << " " << res.item << endl;
    }

    /** 猜对了 */
    ui.cheer();

    /** 猜错了，学习 */
    {
        LearningResult res = ui.learn("ctj12461");
        cout << res.question << endl;
        cout << res.answer << endl;
        cout << res.branch.id << " " << res.branch.item << endl;
    }

    /** 询问要不要再来一次 */
    {
        MenuResult res = ui.again();
        cout << res.id << " " << res.item << endl;
    }

    /** 退出界面 */
    ui.quit();

    return 0;
}
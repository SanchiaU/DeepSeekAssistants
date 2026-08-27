#include "deepseekaiassistants.h"

#include <QApplication>
#include <QIcon>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DeepSeekAIAssistants w;

    w.setMinimumWidth(1100);
    w.setMinimumHeight(700);

    w.setWindowTitle("DeepSeekAIAssistant客户端软件--V1.0");
    w.setWindowIcon(QIcon(":/new/prefix1/images/AILogo.ico"));
    w.show();
    return a.exec();
}

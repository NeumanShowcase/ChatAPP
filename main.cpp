#include "chatmeup.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ChatMeUp w;
    w.show();

    return a.exec();
}

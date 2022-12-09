#include "QtClicker.h"
#include <QtWidgets/QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtClicker w;
    w.show();
    return a.exec();
}

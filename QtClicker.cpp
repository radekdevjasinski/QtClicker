#include "QtClicker.h"
#include <string>
using namespace std;
QtClicker::QtClicker(QWidget *parent) : QMainWindow(parent)
{
    ui.setupUi(this);
    timer.setInterval(2000);
    timer.start();
    connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
}
QtClicker::~QtClicker()
{}
void QtClicker::on_pushButton_clicked()
{
    //
}

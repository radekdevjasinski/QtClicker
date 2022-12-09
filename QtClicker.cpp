#include "QtClicker.h"
#include <string>
using namespace std;
QtClicker::QtClicker(QWidget *parent) : QMainWindow(parent)
{
    ui.setupUi(this);
    timer.setInterval(1000);
    timer.start();
    connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
    init();
    //inicjalizacja
    
}
QtClicker::~QtClicker()
{}
void QtClicker::on_pushButton_clicked()
{
    //
}

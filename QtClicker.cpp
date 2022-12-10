#include "QtClicker.h"
#include <string>
#include <QPixmap>
using namespace std;
QtClicker::QtClicker(QWidget *parent) : QMainWindow(parent)
{
    ui.setupUi(this);
    timer.setInterval(100);
    timer.start();
    connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
    QPixmap pix("logo.png");
    ui.label->setPixmap(pix.scaled(800, 150, Qt::KeepAspectRatio));
    init();

    //inicjalizacja
    
}
QtClicker::~QtClicker()
{}
#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtClicker.h"

class QtClicker : public QMainWindow
{
    Q_OBJECT

public:
    QtClicker(QWidget *parent = nullptr);
    ~QtClicker();
private:
    Ui::QtClickerClass ui;
private slots:

};

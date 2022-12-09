#pragma once

#include <QtWidgets/QMainWindow>
#include <QTimer>
#include "ui_QtClicker.h"

class QtClicker : public QMainWindow
{
    Q_OBJECT

public:
    QtClicker(QWidget *parent = nullptr);
    ~QtClicker();
private:
    Ui::QtClickerClass ui;
    QTimer timer;
private slots:
    void update();
    void on_pushButton_clicked();
};

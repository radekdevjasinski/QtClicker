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
    Ui::QtClickerClass ui;
    QTimer timer;
private slots:
    void update();
    void init();
    void title();
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_11_clicked();
    void on_pushButton_13_clicked();
    void on_pushButton_15_clicked();
};

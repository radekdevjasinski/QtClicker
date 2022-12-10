#include "QtClicker.h"
#include <QtWidgets/QApplication>
#include<cstdio>
#include<iostream>
#include<ctime>
#include<cmath>
#include<stdlib.h>
#include<windows.h>
#include<list>
#include<string>
#include<limits>
#include <fstream>
using namespace std;
int roundToInt(float value)
{
    return (int)(value + 0.5);
}
string MoneyString(int money)
{
    string oldMoney = to_string(money);
    string moneyString = oldMoney;
    int chars = 0;
    for (int i = oldMoney.size() - 1; i >= 0; i--)
    {
        chars++;
        if (chars == 3 && i - 1 >= 0)
        {
            moneyString.insert(i, 1, ',');
            chars = 0;
        }
    }
    return moneyString;
}
class Money
{
public:
    int cash;
    Money()
    {
        cash = 5;
    }
    void MoneyAdd(int cash_)
    {
        cash += cash_;
    }
}money;
class Job {
public:
    string name;
    string desc;

    int level;
    int maxLevel;
    float price;
    float reward;

    time_t startTime;
    float seconds;
    float timeToShow;

    float priceStart;
    float rewardStart;
    float secondsStart;

    float priceEnd;
    float rewardEnd;
    float secondsEnd;

    Job(string name_, string desc_, float price_, float reward_, float seconds_, float priceEnd_, float rewardEnd_, float secondsEnd_)
    {
        name = name_;
        desc = desc_;

        level = -1;
        maxLevel = 20;
        price = price_;

        reward = reward_;
        seconds = seconds_;
        timeToShow = 0;

        priceStart = price;
        rewardStart = reward;
        secondsStart = seconds;

        priceEnd = priceEnd_;
        rewardEnd = rewardEnd_;
        secondsEnd = secondsEnd_;
    }
    void CheckWorkDone()
    {
        if (level >= 0)
        {
            int currentTime = time(NULL);

            int secondsPassed = (currentTime - startTime);
            int CirclesDoneInt = secondsPassed / roundToInt(seconds);
            float CirclesDoneFloat = secondsPassed % roundToInt(seconds);
            int secondsSpare = secondsPassed - CirclesDoneInt * roundToInt(seconds);
            if (CirclesDoneInt >= 1)
            {
                money.MoneyAdd(roundToInt(reward) * CirclesDoneInt);
                startTime = currentTime - secondsSpare;
            }
            if (seconds < 1.5)
            {
                timeToShow = 1;
            }
            else
            {
                timeToShow = (float)(CirclesDoneFloat / roundToInt(seconds));
            }
        }

    }
    void LevelUp()
    {
        price = priceStart + ((priceEnd - priceStart) / maxLevel) * level;
        reward = rewardStart + ((rewardEnd - rewardStart) / maxLevel) * level;
        seconds = secondsStart - ((secondsStart - secondsEnd) / maxLevel) * level;
    }
};
class Game {
public:
    list<Job> jobs;
    list<Job>::iterator it;
    Job j1 = Job("Dropshiping", "Kupujesz taniej sprzedajesz drozej", 2, 1, 5, 20, 20, 1);
    Job j2 = Job("Webmaster", "Tworzysz slabe strony na wordpressie", 20, 5, 10, 100, 40, 5);
    Job j3 = Job("Computer technical support", "Wlaczasz i wylaczasz do skutku", 50, 10, 30, 250, 100, 15);
    Job j4 = Job("Service assistant", "Pracujesz w serwisie u wujka", 100, 25, 45, 500, 250, 27);
    Job j5 = Job("Master programmer", "Umiesz uzywac juz petli for i while", 500, 100, 60, 1000, 500, 35);
    Job j6 = Job("Unity designer", "Robisz podrobki gier, tyko gorzej", 2000, 500, 75, 6000, 3000, 55);
    Job j7 = Job("Bitcoin trader", "Kopiesz bitcoina na starym laptopie babci", 10000, 1000, 90, 60000, 25000, 75);
    Job j8 = Job("Owner of twitter", "Przywracasz wolnosc slowa", 100000, 10000, 120, 500000, 300000, 90);

    bool reset;
    string save;
    string newGame;

    Game() {
        jobs.push_back(j1);
        jobs.push_back(j2);
        jobs.push_back(j3);
        jobs.push_back(j4);
        jobs.push_back(j5);
        jobs.push_back(j6);
        jobs.push_back(j7);
        jobs.push_back(j8);

        reset = false;

        save = "savegame.txt";
        newGame = "newgame.txt";
    }
    string LoadingBar(float time) {
        string loading = "----------", hasz = "";
        int y = 0;

        for (int i = 1; i <= time * 10; i++)
        {
            y++;
            hasz.append("#");
        }
        loading.replace(0, y, hasz);
        return loading;
    }
    void Menu() {
        cout << "IT CAPITALIST \n";
        cout << "CASH: " << MoneyString(money.cash) << " CPU's \n\n"; //money.cash
        for (it = jobs.begin(); it != jobs.end(); ++it)
        {
            cout << it->name << endl;
            cout << it->desc << endl;
            if (it->level != -1)
            {
                cout << "PRICE: " << MoneyString(roundToInt(it->price)) << endl;
                cout << "REWARD: " << MoneyString(roundToInt(it->reward)) << endl;
                cout << "TIME: (" << MoneyString(roundToInt(it->seconds)) << "s) [" << LoadingBar(it->timeToShow) << "]" << endl;
                cout << "LEVEL: " << it->level << " / " << it->maxLevel << "\n\n";
            }
            else
            {
                cout << "LOCKED\n";
                cout << "PRICE: " << MoneyString(roundToInt(it->price)) << "\n\n";
            }

        }
    }
    void Commands(string code)
    {
        string cheatCodes[] = { "alldone", "unlockall", "firstday", "elonmusk" };
        if (code == cheatCodes[0])
        {
            for (it = jobs.begin(); it != jobs.end(); ++it)
            {
                if (it->level == -1)
                {
                    it->startTime = time(NULL);
                }
                it->level = 20;
                it->LevelUp();
            }
            cout << "\nCheated\n" << endl;
        }
        else if (code == cheatCodes[1])
        {
            for (it = jobs.begin(); it != jobs.end(); ++it)
            {
                if (it->level == -1)
                {
                    it->level = 0;
                    it->LevelUp();
                    it->startTime = time(NULL);
                    cout << "\nCheated\n" << endl;
                }
            }
        }
        else if (code == cheatCodes[2])
        {
            if (jobs.begin()->level == -1)
            {
                jobs.begin()->startTime = time(NULL);
            }
            it->level = 20;
            jobs.begin()->LevelUp();
            cout << "\nCheated\n" << endl;
        }
        else if (code == cheatCodes[3])
        {
            money.MoneyAdd(100000);
            cout << "\nCheated\n" << endl;
        }
    }
    void Buy(int number)
    {
        int i = 1;
        for (it = jobs.begin(); it != jobs.end(); ++it)
        {
            if (i == number)
            {
                if (money.cash >= it->price && it->level + 1 <= it->maxLevel)
                {
                    if (it->level == -1)
                    {
                        it->startTime = time(NULL);
                    }
                    money.cash -= roundToInt(it->price);
                    it->level++;
                    it->LevelUp();
                }
            }
            i++;
        }
    }
    void CheckWorkDone()
    {
        for (it = jobs.begin(); it != jobs.end(); ++it)
        {
            it->CheckWorkDone();
        }
    }
    void SaveToFile() 
    {
        ofstream myfile;
        myfile.open("savegame.txt");
        myfile << money.cash << endl;
        for (it = jobs.begin(); it != jobs.end(); ++it)
        {
            myfile << it->name << endl;
            myfile << it->level << endl;
            myfile << it->startTime << endl;
        }
        myfile.close();
    }
    void ReadFromFile(string file)
    {
        for (it = jobs.begin(); it != jobs.end(); ++it)
        {
            it->timeToShow = 0;
            it->level = 0;
            it->LevelUp();
        }
        ifstream myfile;
        string buffor;
        myfile.open(file);
        if (getline(myfile, buffor))
            money.cash = stoi(buffor);
        for (it = jobs.begin(); it != jobs.end(); ++it)
        {
            if (getline(myfile, buffor))
                it->name = buffor;
            if (getline(myfile, buffor))
                it->level = stoi(buffor);
            if (getline(myfile, buffor))
                it->startTime = stoi(buffor);
            if (it->level >= 0)
            {
                it->LevelUp();
            }   

        }
        myfile.close();
    }
}game;
void QtClicker::update()
{
    game.CheckWorkDone();
    showUI();
    game.SaveToFile();
    
}
void QtClicker::init()
{
    showUI();
    game.ReadFromFile(game.save);

}
void QtClicker::showUI()
{
    int i = 1;
    for (game.it = game.jobs.begin(); game.it != game.jobs.end(); ++game.it)
    {
        switch (i)
        {
        case 1:
            if (game.it->level < 0) ui.groupBox->setTitle(QString::fromStdString(game.it->name + " Locked"));
            else ui.groupBox->setTitle(QString::fromStdString(game.it->name + " " + to_string(game.it->level) + "/" + to_string(game.it->maxLevel)));
            ui.progressBar->setValue(game.it->timeToShow * 100);
            if (game.it->level < game.it->maxLevel) ui.pushButton->setText(QString::fromStdString("Buy for " + (MoneyString(roundToInt(game.it->price)))));
            else ui.pushButton->setText(QString::fromStdString("MAX LEVEL"));
            ui.label_4->setText(QString::fromStdString("Reward " + (MoneyString(roundToInt(game.it->reward)))));
            ui.label_3->setText(QString::fromStdString(MoneyString(roundToInt(game.it->seconds)) + "s"));
            if (game.it->price <= money.cash && game.it->level != game.it->maxLevel) ui.pushButton->setStyleSheet("background-color: #16a538 ; color: black;");
            else ui.pushButton->setStyleSheet("color: black;");
            break;
        case 2:
            if (game.it->level < 0) ui.groupBox_2->setTitle(QString::fromStdString(game.it->name + " Locked"));
            else ui.groupBox_2->setTitle(QString::fromStdString(game.it->name + " " + to_string(game.it->level) + "/" + to_string(game.it->maxLevel)));
            ui.progressBar_2->setValue(game.it->timeToShow * 100);
            if (game.it->level < game.it->maxLevel) ui.pushButton_3->setText(QString::fromStdString("Buy for " + (MoneyString(roundToInt(game.it->price)))));
            else ui.pushButton_3->setText(QString::fromStdString("MAX LEVEL"));
            ui.label_6->setText(QString::fromStdString("Reward " + (MoneyString(roundToInt(game.it->reward)))));
            ui.label_5->setText(QString::fromStdString(MoneyString(roundToInt(game.it->seconds)) + "s"));
            if (game.it->price <= money.cash && game.it->level != game.it->maxLevel) ui.pushButton_3->setStyleSheet("background-color: #16a538; color: black;");
            else ui.pushButton_3->setStyleSheet("color: black;");
            break;
        case 3:
            if (game.it->level < 0) ui.groupBox_3->setTitle(QString::fromStdString(game.it->name + " Locked"));
            else ui.groupBox_3->setTitle(QString::fromStdString(game.it->name + " " + to_string(game.it->level) + "/" + to_string(game.it->maxLevel)));
            ui.progressBar_3->setValue(game.it->timeToShow * 100);
            if (game.it->level < game.it->maxLevel) ui.pushButton_5->setText(QString::fromStdString("Buy for " + (MoneyString(roundToInt(game.it->price)))));
            else ui.pushButton_5->setText(QString::fromStdString("MAX LEVEL"));
            ui.label_8->setText(QString::fromStdString("Reward " + (MoneyString(roundToInt(game.it->reward)))));
            ui.label_7->setText(QString::fromStdString(MoneyString(roundToInt(game.it->seconds)) + "s"));
            if (game.it->price <= money.cash && game.it->level != game.it->maxLevel) ui.pushButton_5->setStyleSheet("background-color: #16a538; color: black;");
            else ui.pushButton_5->setStyleSheet("color: black;");
            break;
        case 4:
            if (game.it->level < 0) ui.groupBox_4->setTitle(QString::fromStdString(game.it->name + " Locked"));
            else ui.groupBox_4->setTitle(QString::fromStdString(game.it->name + " " + to_string(game.it->level) + "/" + to_string(game.it->maxLevel)));
            ui.progressBar_4->setValue(game.it->timeToShow * 100);
            if (game.it->level < game.it->maxLevel) ui.pushButton_7->setText(QString::fromStdString("Buy for " + (MoneyString(roundToInt(game.it->price)))));
            else ui.pushButton_7->setText(QString::fromStdString("MAX LEVEL"));
            ui.label_10->setText(QString::fromStdString("Reward " + (MoneyString(roundToInt(game.it->reward)))));
            ui.label_9->setText(QString::fromStdString(MoneyString(roundToInt(game.it->seconds)) + "s"));
            if (game.it->price <= money.cash && game.it->level != game.it->maxLevel) ui.pushButton_7->setStyleSheet("background-color: #16a538; color: black;");
            else ui.pushButton_7->setStyleSheet("color: black;");
            break;
        case 5:
            if (game.it->level < 0) ui.groupBox_5->setTitle(QString::fromStdString(game.it->name + " Locked"));
            else ui.groupBox_5->setTitle(QString::fromStdString(game.it->name + " " + to_string(game.it->level) + "/" + to_string(game.it->maxLevel)));
            ui.progressBar_5->setValue(game.it->timeToShow * 100);
            if (game.it->level < game.it->maxLevel) ui.pushButton_9->setText(QString::fromStdString("Buy for " + (MoneyString(roundToInt(game.it->price)))));
            else ui.pushButton_9->setText(QString::fromStdString("MAX LEVEL"));
            ui.label_12->setText(QString::fromStdString("Reward " + (MoneyString(roundToInt(game.it->reward)))));
            ui.label_11->setText(QString::fromStdString(MoneyString(roundToInt(game.it->seconds)) + "s"));
            if (game.it->price <= money.cash && game.it->level != game.it->maxLevel) ui.pushButton_9->setStyleSheet("background-color: #16a538; color: black;");
            else ui.pushButton_9->setStyleSheet("color: black;");
            break;
        case 6:
            if (game.it->level < 0) ui.groupBox_6->setTitle(QString::fromStdString(game.it->name + " Locked"));
            else ui.groupBox_6->setTitle(QString::fromStdString(game.it->name + " " + to_string(game.it->level) + "/" + to_string(game.it->maxLevel)));
            ui.progressBar_6->setValue(game.it->timeToShow * 100);
            if (game.it->level < game.it->maxLevel) ui.pushButton_11->setText(QString::fromStdString("Buy for " + (MoneyString(roundToInt(game.it->price)))));
            else ui.pushButton_11->setText(QString::fromStdString("MAX LEVEL"));
            ui.label_14->setText(QString::fromStdString("Reward " + (MoneyString(roundToInt(game.it->reward)))));
            ui.label_13->setText(QString::fromStdString(MoneyString(roundToInt(game.it->seconds)) + "s"));
            if (game.it->price <= money.cash && game.it->level != game.it->maxLevel) ui.pushButton_11->setStyleSheet("background-color: #16a538; color: black;");
            else ui.pushButton_11->setStyleSheet("color: black;");
            break;
        case 7:
            if (game.it->level < 0) ui.groupBox_7->setTitle(QString::fromStdString(game.it->name + " Locked"));
            else ui.groupBox_7->setTitle(QString::fromStdString(game.it->name + " " + to_string(game.it->level) + "/" + to_string(game.it->maxLevel)));
            ui.progressBar_7->setValue(game.it->timeToShow * 100);
            if (game.it->level < game.it->maxLevel) ui.pushButton_13->setText(QString::fromStdString("Buy for " + (MoneyString(roundToInt(game.it->price)))));
            else ui.pushButton_13->setText(QString::fromStdString("MAX LEVEL"));
            ui.label_16->setText(QString::fromStdString("Reward " + (MoneyString(roundToInt(game.it->reward)))));
            ui.label_15->setText(QString::fromStdString(MoneyString(roundToInt(game.it->seconds)) + "s"));
            if (game.it->price <= money.cash && game.it->level != game.it->maxLevel) ui.pushButton_13->setStyleSheet("background-color: #16a538; color: black;");
            else ui.pushButton_13->setStyleSheet("color: black;");
            break;
        case 8:
            if (game.it->level < 0) ui.groupBox_8->setTitle(QString::fromStdString(game.it->name + " Locked"));
            else ui.groupBox_8->setTitle(QString::fromStdString(game.it->name + " " + to_string(game.it->level) + "/" + to_string(game.it->maxLevel)));
            ui.progressBar_8->setValue(game.it->timeToShow * 100);
            if (game.it->level < game.it->maxLevel) ui.pushButton_15->setText(QString::fromStdString("Buy for " + (MoneyString(roundToInt(game.it->price)))));
            else ui.pushButton_15->setText(QString::fromStdString("MAX LEVEL"));
            ui.label_18->setText(QString::fromStdString("Reward " + (MoneyString(roundToInt(game.it->reward)))));
            ui.label_17->setText(QString::fromStdString(MoneyString(roundToInt(game.it->seconds)) + "s"));
            if (game.it->price <= money.cash && game.it->level != game.it->maxLevel) ui.pushButton_15->setStyleSheet("background-color: #16a538; color: black;");
            else ui.pushButton_15->setStyleSheet("color: black;");
            break;
        default:
            break;
        }
        i++;
    }
    ui.label_2->setText(QString::fromStdString("Cash: " + MoneyString(money.cash) + " GPU's"));
}
void QtClicker::on_pushButton_clicked()
{
    game.Buy(1);
}
void QtClicker::on_pushButton_3_clicked()
{
    game.Buy(2);
}
void QtClicker::on_pushButton_5_clicked()
{
    game.Buy(3);
}
void QtClicker::on_pushButton_7_clicked()
{
    game.Buy(4);
}
void QtClicker::on_pushButton_9_clicked()
{
    game.Buy(5);
}
void QtClicker::on_pushButton_11_clicked()
{
    game.Buy(6);
}
void QtClicker::on_pushButton_13_clicked()
{
    game.Buy(7);
}
void QtClicker::on_pushButton_15_clicked()
{
    game.Buy(8);
}
void QtClicker::on_pushButton_17_clicked()
{
    if (!game.reset)
    {
        game.reset = true;
        ui.pushButton_17->setStyleSheet("background-color: red; color: white;");
    }
    else
    {
        ui.pushButton_17->setStyleSheet("color: black;");
        game.reset = false;
        game.ReadFromFile(game.newGame);
    }
}
int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    QtClicker w;
    w.show();
    return a.exec();
}
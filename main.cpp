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
using namespace std;
int roundToInt(float value)
{
    return (int)(value + 0.5);
}
string WriteComma(int tempmoney) {
    int num = tempmoney;
    int count = 0, d = 1;
    string str = "";
    if (num == 0)
    {
        str = "0";
        return str;
    }
    while (tempmoney) {
        tempmoney /= 10;
        count++;
        if (tempmoney) d *= 10;
    }
    tempmoney = num;

    while (num) {
        if (count-- % 3 == 0 and tempmoney != num) str += ",";

        str += to_string(num / d);
        num %= d;
        d /= 10;
    }
    return str;
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
            timeToShow = (float)(CirclesDoneFloat / roundToInt(seconds));
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
    Game() {
        jobs.push_back(j1);
        jobs.push_back(j2);
        jobs.push_back(j3);
        jobs.push_back(j4);
        jobs.push_back(j5);
        jobs.push_back(j6);
        jobs.push_back(j7);
        jobs.push_back(j8);
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
        int i = 0;
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
}game;

//int main() {
//    string command;
//    for (;;) {
//        game.Menu();
//        do {
//            cout << "To buy/upgrade a business type: buy (number of business)" << endl;
//            cout << "or \nPress ENTER to reload" << endl;
//            getline(cin, command);
//            game.Commands(command);
//        } while (command.length() != 0);
//        game.ClearScreen();
//        game.CheckWorkDone();
//    }
//    return 0;
//
//}
void QtClicker::update()
{
    title();
    game.CheckWorkDone();
}
void QtClicker::init()
{
    title();
    ui.label_2->setText(QString::fromStdString("Cash: " + WriteComma(money.cash) + " GPU's"));
}
void QtClicker::title()
{
    int i = 1;
    for (game.it = game.jobs.begin(); game.it != game.jobs.end(); ++game.it)
    {
        switch (i)
        {
        case 1:
            if (game.it->level <= 0) ui.groupBox->setTitle(QString::fromStdString(game.it->name + " Locked"));
            else ui.groupBox->setTitle(QString::fromStdString(game.it->name + " " + to_string(game.it->level) + "/" + to_string(game.it->maxLevel)));
            ui.progressBar->setValue(game.it->timeToShow);
            break;
        case 2:
            if (game.it->level <= 0) ui.groupBox_2->setTitle(QString::fromStdString(game.it->name + " Locked"));
            else ui.groupBox_2->setTitle(QString::fromStdString(game.it->name + " " + to_string(game.it->level) + "/" + to_string(game.it->maxLevel)));
            ui.progressBar_2->setValue(game.it->timeToShow);
            break;
        case 3:
            if (game.it->level <= 0) ui.groupBox_3->setTitle(QString::fromStdString(game.it->name + " Locked"));
            else ui.groupBox_3->setTitle(QString::fromStdString(game.it->name + " " + to_string(game.it->level) + "/" + to_string(game.it->maxLevel)));
            ui.progressBar_3->setValue(game.it->timeToShow);
            break;
        case 4:
            if (game.it->level <= 0) ui.groupBox_4->setTitle(QString::fromStdString(game.it->name + " Locked"));
            else ui.groupBox_4->setTitle(QString::fromStdString(game.it->name + " " + to_string(game.it->level) + "/" + to_string(game.it->maxLevel)));
            ui.progressBar_4->setValue(game.it->timeToShow);
            break;
        case 5:
            if (game.it->level <= 0) ui.groupBox_5->setTitle(QString::fromStdString(game.it->name + " Locked"));
            else ui.groupBox_5->setTitle(QString::fromStdString(game.it->name + " " + to_string(game.it->level) + "/" + to_string(game.it->maxLevel)));
            ui.progressBar_5->setValue(game.it->timeToShow);
            break;
        case 6:
            if (game.it->level <= 0) ui.groupBox_6->setTitle(QString::fromStdString(game.it->name + " Locked"));
            else ui.groupBox_6->setTitle(QString::fromStdString(game.it->name + " " + to_string(game.it->level) + "/" + to_string(game.it->maxLevel)));
            ui.progressBar_6->setValue(game.it->timeToShow);
            break;
        case 7:
            if (game.it->level <= 0) ui.groupBox_7->setTitle(QString::fromStdString(game.it->name + " Locked"));
            else ui.groupBox_7->setTitle(QString::fromStdString(game.it->name + " " + to_string(game.it->level) + "/" + to_string(game.it->maxLevel)));
            ui.progressBar_7->setValue(game.it->timeToShow);
            break;
        case 8:
            if (game.it->level <= 0) ui.groupBox_8->setTitle(QString::fromStdString(game.it->name + " Locked"));
            else ui.groupBox_8->setTitle(QString::fromStdString(game.it->name + " " + to_string(game.it->level) + "/" + to_string(game.it->maxLevel)));
            ui.progressBar_8->setValue(game.it->timeToShow);
            break;
        default:
            break;
        }
        i++;
    }
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtClicker w;
    w.show();
    return a.exec();
}

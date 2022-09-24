// Pimonova_labs_plusi.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <limits>
using namespace std;

enum menu { exitMenu, addPipe, addStation, viewObjects, editPipe, editStation, save, download };

//functions

void skip()
{
    if (cin.fail())
    {
        cin.clear();
        for (uint8_t ch; cin >> ch;)
        { 
            if (isdigit(ch) || ch == '-')
            {
                cin.unget(); 
                return;
            }
        }
    }
    cout << ("No input");
}

uint32_t getUInt() // Ввод беззнакового инта
{
    uint32_t x;
    while (true)
    {
        if (cin >> x) return x;
        cout << "Try again:\n";
        skip();
    }
}

double_t getDouble() // Ввод вещественного числа
{
    double x;
    while (true)
    {
        if (cin >> x) return x;
        cout << "Try again:\n";
        skip();
    }
}

uint32_t getInRange(uint8_t x1,uint8_t x2) // Ввод числа в диапазоне
{
    while (true)
    {
        uint32_t x = getUInt();
        if (x1<=x && x<=x2) return x;
        cout << "Try again:\n";
    }
}

int main()
{
	cout << "Welcome to the main menu \nUse numbers to navigate:\n";
	cout << "Exit:0 \nAdd pipe:1 \nAdd station:2 \nView objects:3 \nEdit pipe:4 \nEdit station:5 \nSave:6 \nDownload:7 \n";

    cout << "Enter an operation: ";
    uint32_t operation = getInRange(0,7);

    switch (operation)
    {
    case menu::exitMenu:
        cout << "Zero";
        break;
    case menu::addPipe:
        cout << "One";
        break;
    case menu::addStation:
        cout << "Two";
        break;
    case menu::viewObjects:
        cout << "Three";
        break;
    case menu::editPipe:
        cout << "Four";
        break;
    case menu::editStation:
        cout << "Five";
        break;
    case menu::save:
        cout << "Six";
        break;
    case menu::download:
        cout << "Seven";
        break;
    }

    /*cout << "Double: ";
    double_t chisldouble = getDouble();
    cout << "OK \n";

    cout << "In diapason 0-100: \n";
    uint32_t chislzero = getInRange(0,100);
    cout << "OK \n"; */

    return 0;
}



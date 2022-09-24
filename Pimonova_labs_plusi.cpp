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


int main()
{
	cout << "Welcome to the main menu \nUse numbers to navigate:\n";
	cout << "Exit:0 \nAdd pipe:1 \nAdd station:2 \nView objects:3 \nEdit pipe:4 \nSave:5 \nDownload:6 \n";

    cout << "Enter an operation: ";
    uint32_t operation = getUInt();
    cout << "OK \n";

    cout << "Double: ";
    double_t chisldouble = getDouble();
    cout << "OK \n";
    cout << chisldouble/2;

    return 0;
}



// Pimonova_labs_plusi.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <limits>
using namespace std;

enum menu { exitMenu, addPipe, addStation, viewObjects, editPipe, editStation, save, download };

struct pipe
{
    double length, diameter;
    bool repair;
};

struct station
{
    string name;
    uint32_t numOfWorkshops, numOfWorkingWorkshops, efficiency;
};

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

bool getBool() // Ввод вещественного числа
{
    bool x;
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
    struct pipe pipe1;
    struct station station1;

    while (true)
    {
        cout << "Welcome to the main menu \nUse numbers to navigate:\n";
        cout << "Exit:0 \nAdd pipe:1 \nAdd station:2 \nView objects:3 \nEdit pipe:4 \nEdit station:5 \nSave:6 \nDownload:7 \n";

        cout << "Enter an operation: ";
        uint32_t operation = getInRange(0, 7);

        switch (operation)
        {
        case menu::exitMenu:
            cout << "Bye!\n";
            exit(0);
            break;
        case menu::addPipe:
            system("cls");
            cout << "Add pipe parameters: length, diameter, repair\n";
            cout << "Length:\n";
            pipe1.length = getDouble();
            cout << "Diameter:\n";
            pipe1.diameter = getDouble();
            cout << "Repair:\n";
            cin >> pipe1.repair;
            break;
        case menu::addStation:
            system("cls");
            cout << "Add the parameters of the compressor station:\nname, number of workshops, number of working workshops, efficiency \n";
            cout << "Name:\n";
            cin >> station1.name;
            cout << "Number of workshops:\n";
            station1.numOfWorkshops = getUInt();
            cout << "Number of working workshops:\n";
            station1.numOfWorkingWorkshops = getInRange(0, station1.numOfWorkshops);
            cout << "Efficiency (0-100):\n";
            station1.efficiency = getInRange(0, 100);
            break;
        case menu::viewObjects:
            system("cls");
            cout << "Pipe:\n";
            cout << "Length: " << pipe1.length << " Diameter: " << pipe1.diameter << " Repair: " << pipe1.repair << endl;
            cout << "Station:\n";
            cout << "Name: " << station1.name << " Number of workshops: " << station1.numOfWorkshops << "\nNumber of working workshops: " << station1.numOfWorkingWorkshops << " Efficiency: " << station1.efficiency << endl;
            cout << "\n";
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
    }
    /*cout << "Double: ";
    double_t chisldouble = getDouble();
    cout << chisldouble / 2;
    cout << "OK \n";

    cout << "In diapason 0-100: \n";
    uint32_t chislzero = getInRange(0,100);
    cout << "OK \n"; */

    return 0;
}



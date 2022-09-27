// Pimonova_labs_plusi.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <limits>
using namespace std;

enum mainMenu { exitMenu, addPipe, addStation, viewObjects, editPipe, editStation, save, download };
enum pipeMenu {length = 11, diameter = 12, repair = 13};
enum stationMenu { name = 21, numOfWorkshops = 22, numOfWorkingWorkshops= 23 , efficiency = 24};

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

uint32_t getUInt()
{
    uint32_t x;
    do
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cin >> x;
    } while (cin.fail() || cin.get() != '\n');
    return x;
}

double getDouble()
{
    double x;
    do
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cin >> x;
    } while (cin.fail() || cin.get() != '\n');
    return x;
}

/*void skip()
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
} */

/* uint32_t getUInt() // Ввод беззнакового инта
{
    uint32_t x;
    while (true)
    {
        if (cin >> x) return x;
        cout << "Try again:\n";
        skip();
    }
} */

/* double_t getDouble() // Ввод вещественного числа
{
    double x;
    while (true)
    {
        if (cin >> x) return x;
        cout << "Try again:\n";
        skip();
    }
} */

/* bool getBool() // Ввод вещественного числа
{
    bool x;
    while (true)
    {
        if (cin >> x) return x;
        cout << "Try again:\n";
        skip();
    }
} */

uint32_t getInRange(uint8_t x1,uint8_t x2) // Ввод числа в диапазоне
{
    uint32_t x = getUInt();
    while (true)
    {
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
        case mainMenu::exitMenu:
            cout << "Bye!\n";
            exit(0);
            break;
        case mainMenu::addPipe:
            system("cls");
            cout << "Add pipe parameters: length, diameter, repair\n";
            cout << "Length:\n";
            pipe1.length = getDouble();
            cout << "Diameter:\n";
            pipe1.diameter = getDouble();
            cout << "Repair:\n";
            cin >> pipe1.repair;
            break;
        case mainMenu::addStation:
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
        case mainMenu::viewObjects:
            system("cls");
            cout << "Pipe:\n";
            cout << "Length: " << pipe1.length << " Diameter: " << pipe1.diameter << " Repair: " << pipe1.repair << endl;
            cout << "Station:\n";
            cout << "Name: " << station1.name << " Number of workshops: " << station1.numOfWorkshops << "\nNumber of working workshops: " << station1.numOfWorkingWorkshops << " Efficiency: " << station1.efficiency << endl;
            cout << "\n";
            break;
        case mainMenu::editPipe:
            cout << "What do you want to change?\n";
            cout << "Length:11 \nDiameter:12 \nRepair:13 \n";
            cout << "Enter number: ";
            uint32_t numberEditPipe = getUInt();
            switch (numberEditPipe)
            {
                case pipeMenu::length:
                    pipe1.length = getDouble();
                    break;
                case pipeMenu::diameter:
                    pipe1.diameter = getDouble();
                    break;
                case pipeMenu::repair:
                    cin >> pipe1.repair;
                    break;
            }
            break;
        case mainMenu::editStation:
            cout << "What do you want to change?\n";
            cout << "Name:21 \nNumber of workshops:22 \nNumber of working workshops:23 \nEfficiency:24 \n";
            uint32_t numberEditStation = getUInt();
            switch (numberEditStation)
            {
            case stationMenu::name:
                cin >> station1.name;
                break;
            case stationMenu::numOfWorkshops:
                station1.numOfWorkshops = getUInt();
                break;
            case stationMenu::numOfWorkingWorkshops:
                station1.numOfWorkingWorkshops = getInRange(0, station1.numOfWorkshops);
                break;
            case stationMenu::efficiency:
                station1.efficiency = getInRange(0, 100);
                break;
            }
            break;
        case mainMenu::save:
            cout << "Six";
            break;
        case mainMenu::download:
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



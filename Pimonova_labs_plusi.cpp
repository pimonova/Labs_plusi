// Pimonova_labs_plusi.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <limits>
#include <fstream>
#include <string>

using namespace std;

// enums

enum mainMenu { exitMenu, addPipe, addStation, viewObjects, editPipe, editStation, save, download };
enum pipeMenu {length = 11, diameter = 12, repair = 13};
enum stationMenu { name = 21, numOfWorkshops = 22, numOfWorkingWorkshops= 23 , efficiency = 24};

// structures

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

void showMenu()
{
    cout << "Welcome to the main menu \nUse numbers to navigate:\n";
    cout << "\n";
    cout << "Exit:0 \nAdd pipe:1 \nAdd station:2 \nView objects:3 \nEdit pipe:4 \nEdit station:5 \nSave:6 \nDownload:7 \n";
    cout << "\n";
}

// функции для проверки

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

// функции добалвния новых элементов

void addPipes(pipe& x)
{
    cout << "Add pipe parameters: length, diameter, repair\n";
    cout << "Length:\n";
    x.length = getDouble();
    cout << "Diameter:\n";
    x.diameter = getDouble();
    cout << "Repair:\n";
    x.repair = getInRange(0, 1);
}

void addStations(station& x)
{
    cout << "Add the parameters of the compressor station:\nname, number of workshops, number of working workshops, efficiency \n";
    cout << "Name:\n";
    getline(cin, x.name);
    cout << "Number of workshops:\n";
    x.numOfWorkshops = getUInt();
    cout << "Number of working workshops:\n";
    x.numOfWorkingWorkshops = getInRange(0, x.numOfWorkshops);
    x.efficiency = numOfWorkingWorkshops / numOfWorkshops * 100;
}

// функции просмотра добавленных элементов

void viewPipes(pipe x)
{
    cout << "Pipe:\n";
    cout << "Length: " << x.length << " Diameter: " << x.diameter << " Repair: " << x.repair << endl;
}

void viewStations(station x)
{
    cout << "Station:\n";
    cout << "Name: " << x.name << " Number of workshops: " << x.numOfWorkshops << "\nNumber of working workshops: " << x.numOfWorkingWorkshops << " Efficiency: " << x.efficiency << endl;
}

// функции изменения добавленных элементов

void editPipeRepair(pipe& x)
{
    cout << "Re-enter the 'under repair' parameter:" << endl;
    x.repair=getInRange(0, 1);
}

void editStationWorkingWorkshops(station& x)
{
    cout << "Re-enter the number of working workshops:" << endl;
    x.numOfWorkingWorkshops = getInRange(0, x.numOfWorkshops);
}

// функции для работы с файлами

void saveToFile(const pipe& p, const station& s)
{
    cout << "Enter the file name (.txt): ";
    string oFileName;
    cin >> oFileName;
    ofstream fout;
    fout.open(oFileName);
    fout << s.name << endl << s.numOfWorkshops << endl << s.numOfWorkingWorkshops << endl << s.efficiency << endl;
    fout << p.length << endl << p.diameter << endl << p.repair;
    fout.close();
    cout << "Data saved!" << endl;
}

void downloadFromFile( pipe& p, station& s)
{
    cout << "Enter the file name (.txt): ";
    string iFileName;
    cin >> iFileName;
    ifstream fin;
    fin.open(iFileName);
    if (!fin.is_open()) 
        cerr << "The file cannot be opened\n"; 
    else
    {
        getline(fin, s.name);
        fin >> s.numOfWorkshops;
        fin >> s.numOfWorkingWorkshops;
        fin >> s.efficiency;
        fin >> p.length;
        fin >> p.diameter;
        fin >> p.repair;
        fin.close();
        cout << "Data uploaded!" << endl;
    }
}

int main()
{
    struct pipe pipe1{};
    struct station station1{};

    while (true)
    {
        showMenu();
        cout << "Enter an operation: ";
        uint32_t operation = getInRange();

        switch (operation)
        {
        case mainMenu::exitMenu:
            cout << "Bye!\n";
            exit(0);
            break;
        case mainMenu::addPipe:
            system("cls");
            addPipes(pipe1);
            break;
        case mainMenu::addStation:
            system("cls");
            addStations(station1);
            break;
        case mainMenu::viewObjects:
            system("cls");
            viewPipes(pipe1);
            viewStations(station1);
            cout << "\n";
            break;
        case mainMenu::editPipe:
            system("cls");
            editPipeRepair(pipe1);
            break;
        case mainMenu::editStation:
            system("cls");
            editStationWorkingWorkshops(station1);
            break;
        case mainMenu::save:
            system("cls");
            saveToFile(pipe1, station1);
            break;
        case mainMenu::download:
            system("cls");
            char buff = 0;
            downloadFromFile(pipe1, station1);
            cout << buff << endl;
            break;
        }
    }

    return 0;
}



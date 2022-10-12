// Pimonova_labs_plusi.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// enums

enum mainMenu { exitMenu, addPipe, addStation, viewObjects, editPipe, editStation, save, download };

// structures

struct pipe
{
    double length, diameter;
    uint32_t repair;
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
    while ((cin >> x).fail() || x == 0)
    {
        cout << "Try again: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    return x;
}

double_t getDouble()
{
    double_t x;
    while ((cin >> x).fail() || x <= 0)
    {
        cout << "Try again: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    return x;
}

uint32_t getInRange(uint8_t x1, uint8_t x2)
{
    uint32_t x;
    while ((cin >> x).fail() || x1 > x || x > x2)
    {
        cout << "Try again: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    return x;
}

// функции добавления новых элементов

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
    cin >> ws;
    getline(cin, x.name);
    cout << "Number of workshops:\n";
    x.numOfWorkshops = getUInt();
    cout << "Number of working workshops:\n";
    x.numOfWorkingWorkshops = getInRange(0, x.numOfWorkshops);
    x.efficiency = double(x.numOfWorkingWorkshops * 100) / x.numOfWorkshops;
}

// функции просмотра добавленных элементов

void viewPipes(const pipe& x)
{
    cout << "Pipe:\n";
    cout << "Length: " << x.length << " Diameter: " << x.diameter << " Repair: " << x.repair << endl;
}

void viewStations(const station& x)
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
    x.numOfWorkingWorkshops = getInRange(1, x.numOfWorkshops);
    x.efficiency = double(x.numOfWorkingWorkshops * 100) / x.numOfWorkshops;
} 

// функции для работы с файлами

void saveToFile(const pipe& p, const station& s)
{
    cout << "Enter the file name: ";
    string oFileName;
    cin >> ws;
    getline(cin,oFileName);
    oFileName = oFileName + ".txt";
    ofstream fout;
    fout.open(oFileName);
    if (!fout.is_open())
        cerr << "The file cannot be opened\n";
    else
    {
        string sFlag, pFlag;
        if (!(s.numOfWorkshops == 0))
        {
            fout << "station" << endl << s.name << endl << s.numOfWorkshops << endl << s.numOfWorkingWorkshops << endl << s.efficiency << endl;
        }
        
        if (!(p.diameter == 0))
        {
            fout << "pipe" << endl << p.length << endl << p.diameter << endl << p.repair << endl;
        }
    }

    fout.close();
    cout << "Data saved!" << endl;
}

void downloadFromFile( pipe& p, station& s)
{
    cout << "Enter the file name (.txt): ";
    string iFileName;
    cin >> ws;
    getline(cin,iFileName);
    iFileName = iFileName + ".txt";
    ifstream fin;
    fin.open(iFileName);
    if (!fin.is_open()) 
        cerr << "The file cannot be opened\n"; 
    else
    {
        while (!fin.eof())
        {
            string line;
            fin >> ws;
            getline(fin, line);
            if (line == "station")
            {
                fin >> ws;
                getline(fin, s.name);
                fin >> s.numOfWorkshops;
                fin >> s.numOfWorkingWorkshops;
                fin >> s.efficiency;
            }

            if (line == "pipe")
            {
                fin >> p.length;
                fin >> p.diameter;
                fin >> p.repair;
            }
        }
        
        cout << "Data uploaded!" << endl;
        
        fin.close();
    }
}

int main()
{
    pipe pipe1{};
    station station1{};

    while (true)
    {
        showMenu();
        cout << "Enter an operation: ";
        uint32_t operation;
        operation = getInRange(0, 7);

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
            downloadFromFile(pipe1, station1);
            break;
        }
    }

    return 0;
}



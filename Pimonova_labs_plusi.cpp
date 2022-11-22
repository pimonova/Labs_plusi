// Pimonova_labs_plusi.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "CPipe.h"
#include "CStation.h"
#include "Utils.h"
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include "Pimonova_labs_plusi.h"


using namespace std;

// enums

enum mainMenu { exitMenu, addPipe, addStation, viewObjects, editPipe, editStation, pipeSearch, stationSearch, save, download };

//functions

void showMenu()
{
    cout << "Welcome to the main menu \nUse numbers to navigate:\n";
    cout << "\n";
    cout << "0. Exit \n1. Add pipe" << endl
         << "2. Add station \n3. View all objects" << endl
         << "4. Edit pipe \n5. Edit station" << endl
         << "6. Pipe search\n7. Station search" << endl
         << "8. Save to file \n9. Download from file \n";
    cout << "\n";
}

// функции изменения добавленных элементов

void editPipeRepair(CPipe& x)
{
    cout << "Re-enter the 'under repair' parameter:" << endl;
    x.repair=getInRange(0, 1);
} 

void editStationWorkingWorkshops(CStation& x)
{
    cout << "Re-enter the number of working workshops:" << endl;
    x.numOfWorkingWorkshops = getInRange(1, x.numOfWorkshops);
    x.efficiency = double(x.numOfWorkingWorkshops * 100) / x.numOfWorkshops;
}

// функции для работы с файлами

void LoadStation(ifstream& fin, CStation& s)
{
    uint32_t id;
    fin >> id;
    s.setStationID(id);
    fin >> ws;
    getline(fin, s.name);
    fin >> s.numOfWorkshops;
    fin >> s.numOfWorkingWorkshops;
    fin >> s.efficiency;
}

void LoadPipe(ifstream& fin, CPipe& p)
{
    uint32_t id;
    fin >> id;
    p.setPipeID(id);
    fin >> p.length;
    fin >> p.diameter;
    fin >> p.repair;
}

void saveToFile(unordered_map<int, CPipe>& mP, unordered_map<int, CStation>& mS)
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
        if (mP.size() != 0)
        {
            for (auto& [pID, p] : mP)
            {
                fout << "pipe" << endl;
                fout << p.getPipeID() << std::endl << p.length << std::endl << p.diameter << std::endl << p.repair << std::endl;
            }

        }
        if (mS.size() != 0)
        {
            for (auto& [sID, s] : mS)
            {
                fout << "station" << endl;
                fout << s.getStationID() << std::endl << s.name << endl << s.numOfWorkshops << endl << s.numOfWorkingWorkshops << endl << s.efficiency << endl;
            }

        }
    }

    fout.close();
    cout << "Data saved!" << endl;
}

void downloadFromFile(unordered_map<int, CPipe>& mP, unordered_map<int, CStation>& mS)
{
    CPipe p;
    CStation s;
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
                LoadStation(fin, s);
                mS.insert({ s.getStationID(), s });
            }

            if (line == "pipe")
            {
                LoadPipe(fin, p);
                mP.insert({ p.getPipeID(), p });
            }
        }
        
        cout << "Data uploaded!" << endl;
        
        fin.close();
    }
} 

CPipe& selectPipe(unordered_map<int, CPipe>& mP)
{
    cout << "Enter pipe ID: ";
    uint32_t userID;
    getCorrect(userID);
    while (mP.find(userID)==mP.end())
    {
        cout << "Error! There is no pipe with this id\n";
        cout << "Enter pipe ID: ";
        getCorrect(userID);
    }
    return mP[userID];
}

CStation& selectStation(unordered_map<int, CStation>& mS)
{
    cout << "Enter station ID: ";
    uint32_t userID;
    getCorrect(userID);
    while (mS.find(userID) == mS.end())
    {
        cout << "Error! There is no station with this id\n";
        cout << "Enter station ID: ";
        getCorrect(userID);
    }
    return mS[userID];
}

int main()
{
    unordered_map<int, CPipe> manyPipes;
    unordered_map<int, CStation> manyStations;

    while (true)
    {
        showMenu();
        cout << "Enter an operation: ";
        uint32_t operation;
        operation = getInRange(0, 9);

        switch (operation)
        {
        case mainMenu::exitMenu:
            cout << "Bye!\n";
            exit(0);
            break;
        case mainMenu::addPipe:
        {
            system("cls");
            CPipe pipe;
            cin >> pipe;
            manyPipes.insert({ pipe.getPipeID(), pipe });
            break;
        }
        case mainMenu::addStation:
        {
            system("cls");
            CStation station;
            cin >> station;
            manyStations.insert({ station.getStationID(), station });
            break;
        }
        case mainMenu::viewObjects:
        {
            system("cls");
            if (manyPipes.size() != 0)
            {
                for (const auto& [pID, p] : manyPipes)
                {
                    cout << p << endl;
                }

            }
            else
            {
                cout << "There are no pipes!";
            }
            if (manyStations.size() != 0)
            {
                for (const auto& [sID, s] : manyStations)
                {
                    cout << s << endl;
                }

            }
            else
            {
                cout << "There are no stations!";
            }
            break;
        }
        case mainMenu::editPipe:
            system("cls");
            editPipeRepair(selectPipe(manyPipes));
            break;
        case mainMenu::editStation:
            system("cls");
            editStationWorkingWorkshops(selectStation(manyStations));
            break;
            case mainMenu::save:
            system("cls");
            saveToFile(manyPipes, manyStations);
            break;
        case mainMenu::download:
            system("cls");
            downloadFromFile(manyPipes, manyStations);
            break;
        case mainMenu::pipeSearch:

            break;
        case mainMenu::stationSearch:

            break;
        }
    }

    return 0;
}



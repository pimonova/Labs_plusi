// Pimonova_labs_plusi.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "CPipe.h"
#include "CStation.h"
#include "Utils.h"
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include "Pimonova_labs_plusi.h"


using namespace std;

// enums

enum mainMenu { exitMenu, addPipe, addStation, viewObjects, editPipe, editStation, pipeSearch, stationSearch, save, download, deletePipe, deleteStation, packageEdit };

//functions

void showMenu()
{
    cout << endl;
    cout << "Welcome to the main menu! \nUse numbers to navigate:\n";
    cout << "\n";
    cout << "0. Exit \n1. Add pipe" << endl
         << "2. Add station \n3. View all objects" << endl
         << "4. Edit pipe \n5. Edit station" << endl
         << "6. Pipe search\n7. Station search" << endl
         << "8. Save to file \n9. Download from file \n"
         << "10. Delete pipe \n11. Delete station \n"
         << "12. Package editing of pipes\n";
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
                fout << p << endl;
            }

        }
        if (mS.size() != 0)
        {
            for (auto& [sID, s] : mS)
            {
                fout << "station" << endl;
                fout << s << endl;
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
                fin >> s;
                mS.insert({ s.getStationID(), s });
            }

            if (line == "pipe")
            {
                fin >> p;
                mP.insert({ p.getPipeID(), p });
            }
        }
        
        cout << "Data uploaded!" << endl;
        
        fin.close();
    }
} 

// выбор объектов

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

// удаление единицы объекта

void deleteOnePipe(unordered_map<int, CPipe>& mP)
{
    CPipe p = selectPipe(mP);
    mP.erase(p.getPipeID());
    cout << "Pipe removed!" << endl;
}

void deleteOneStaton(unordered_map<int, CStation>& mS)
{
    CStation s = selectStation(mS);
    mS.erase(s.getStationID());
    cout << "Station removed!" << endl;
}

// поиск по станциям

template<typename T>
using Filter1 = bool(*)(const CStation& s, T parameter);

bool checkByName(const CStation& s, string parameter)
{
    return s.name.find(parameter) != string::npos;
}

bool checkByNotWorkingWorkshops(const CStation& s, double parameter)
{
    return (double((s.numOfWorkshops -s.numOfWorkingWorkshops) * 100) / s.numOfWorkshops) >= parameter;
}

template<typename T>
vector<uint32_t> findStationByFilter(unordered_map<int, CStation>& mS, Filter1<T> f, T parameter)
{
    vector<uint32_t> result;

    for (auto& [sID, s] : mS)
    {
        if (f(s, parameter))
        {
            result.push_back(s.getStationID());
        }
    }

    if (result.empty())
    {
        cout << "There are no pipes wuth this parameter\n";
    }

    return result;
}

// поиск по трубам

template<typename T>
using Filter2 = bool(*)(const CPipe& p, T parameter);

bool checkByID(const CPipe& p, uint32_t parameter)
{
    return p.getPipeID() >= parameter;
}

bool checkByRepair(const CPipe& p, uint32_t parameter)
{
    return p.repair == parameter;
}

template<typename T>
vector<uint32_t> findPipeByFilter(unordered_map<int, CPipe>& mP, Filter2<T> f, T parameter)
{
    vector<uint32_t> result;

    for (auto& [pID, p] : mP)
    {
        if (f(p, parameter))
        {
            result.push_back(p.getPipeID());
        }
    }

    if (result.empty())
    {
        cout << "There are no pipes with this parameter\n";
    }

    return result;
}

vector<uint32_t> searchPipe(unordered_map<int, CPipe>& mP)
{
    vector<uint32_t> result{};
    cout << "Enter the search parameter: \n"
        << "1 - find pipe by IDs; \n"
        << "2 - find pipe by the repair\n";
    if (getInRange(1, 2) == 1)
    {
        uint32_t pID;
        cout << "Enter pipe IDs: ";
        getCorrect(pID);
        result = findPipeByFilter(mP, checkByID, pID);
        for (uint32_t i : result)
        {
            cout << mP[i];
        }
    }
    else
    {
        uint32_t repair;
        cout << "Enter marker of repair: ";
        repair = getInRange(0, 1);
        result = findPipeByFilter(mP, checkByRepair, repair);
        for (uint32_t i : result)
        {
            cout << mP[i];
        }
    }

    return result;
}

// пакетное редактирование

void PacketEditPipe(unordered_map<int, CPipe>& mP)
{
    vector<uint32_t> allResult;
    allResult = searchPipe(mP);
    
    if (allResult.size() != 0)
    {
        cout << "Enter the edit parameter: \n"
            << "1 - edit all find pipes; \n"
            << "2 - edit some find pipes\n";
        if (getInRange(1, 2) == 1)
        {
            cout << "Enter the repair parameter: \n"
                << "1 - all pipes are working; \n"
                << "2 - all pipes under repair\n";
            if (getInRange(1, 2) == 1)
            {
                for (auto& id : allResult)
                    mP[id].repair = 1;
            }
            else
            {
                for (auto& id : allResult)
                    mP[id].repair = 0;
            }
        }
        else
        {
            vector <int> someResult;
            while (true)
            {
                cout << "Enter pipe's id to edit or 0 to complete: ";
                uint32_t i;
                i = getInRange(0, *max_element(allResult.begin(), allResult.end()));
                if (i)
                {
                    if (mP.find(i) == mP.end())
                        cout << "Error! There is no pipe with this id\n";
                    else
                        someResult.push_back(i);
                }
                else
                    break;
            }

            cout << "Enter the repair parameter: \n"
                << "1 - all pipes are working; \n"
                << "2 - all pipes under repair\n";
            if (getInRange(1, 2) == 1)
            {
                for (auto& id : someResult)
                    mP[id].repair = 1;
            }
            else
            {
                for (auto& id : someResult)
                    mP[id].repair = 0;
            }
        }
    }
    else
    {
        cout << "No pipes in filter -> no packet editing\n";
    }

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
        operation = getInRange(0, 12);

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
                cout << "There are no pipes!\n";
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
                cout << "There are no stations!\n";
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
            system("cls");
            searchPipe(manyPipes);
            break;
        case mainMenu::stationSearch:
        {
            system("cls");
            cout << "Enter the search parameter: \n"
                << "1 - find station by name; \n"
                << "2 - find station by the percentage of unused workshops\n";
            if (getInRange(1, 2) == 1)
            {
                string name;
                cout << "Enter station name: ";
                cin >> ws;
                getline(cin, name);
                for (uint32_t i : findStationByFilter(manyStations, checkByName, name))
                {
                    cout << manyStations[i];
                }
            }
            else
            {
                double percent;
                cout << "Enter percent of not working workshops: ";
                getCorrect(percent);
                for (uint32_t i : findStationByFilter(manyStations, checkByNotWorkingWorkshops, percent))
                {
                    cout << manyStations[i];
                }
            }
            
            break;
        }
        case mainMenu::deletePipe:
            system("cls");
            deleteOnePipe(manyPipes);
            break;
        case mainMenu::deleteStation:
            system("cls");
            deleteOneStaton(manyStations);
            break;
        case mainMenu::packageEdit:
            system("cls");
            PacketEditPipe(manyPipes);
            break;
        }
    }

    return 0;
}



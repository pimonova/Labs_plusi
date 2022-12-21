#pragma once
#include <unordered_map>
#include <vector>
#include "CPipe.h"
#include "CStation.h"
#include "Utils.h"

class CGasTransportingNetwork
{
    // контейнеры для графа
    std::vector<std::vector<uint32_t>> ribs;

    std::vector<std::vector<double>> weightsMatrix;

    std::vector<std::vector<uint32_t>> throughputMatrix;

    //функции для графа

    std::unordered_map<uint32_t, uint32_t> createIndexOfVertices(const std::unordered_map<uint32_t, CPipe>&, std::unordered_map<uint32_t, CStation>&);

    std::unordered_map<uint32_t, uint32_t> createIndexOfVerticesReverse(const std::unordered_map<uint32_t, CPipe>&, std::unordered_map<uint32_t, CStation>&);

    std::vector<std::vector<uint32_t>> createGraph(const std::unordered_map<uint32_t, CPipe>&, std::unordered_map<uint32_t, CStation>&);
    
    std::vector<std::vector<double>> createMatrixWeights(const std::unordered_map<uint32_t, CPipe>&, std::unordered_map<uint32_t, CStation>&);

    std::vector<std::vector<uint32_t>> createMatrixThroughput(const std::unordered_map<uint32_t, CPipe>&, std::unordered_map<uint32_t, CStation>&);



public:
	void showConnection(const std::unordered_map<uint32_t, CPipe>&, const std::unordered_map<uint32_t, CStation>&);

	void addConnection(std::unordered_map<uint32_t, CPipe>&, std::unordered_map<uint32_t, CStation>&);

	void deleteConnection(std::unordered_map<uint32_t, CPipe>&, std::unordered_map<uint32_t, CStation>&);

    template<typename T>
    void deleteItems(std::unordered_map<uint32_t, T>& map)
    {
        std::cout << "Enter id to delete element: ";
        uint32_t id = getCorrect(id);
        if (SearchId(map, id) != -1)
        {
            if (map.at(id).linked())
            {
                std::cout << "Element in gas transporting system, so disconnect it first!" << std::endl;
                return;
            }
            else
            {
                map.erase(id);
                std::cout << "Element removed!" << std::endl;
                return;
            }
        }
        else
            std::cout << "There are no elements with this ID\n";
    }


};

bool checkByDiameter(const CPipe& p, double parameter);


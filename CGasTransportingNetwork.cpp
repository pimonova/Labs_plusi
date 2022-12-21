#pragma once
#include "CGasTransportingNetwork.h"
#include "Cpipe.h"
#include "CStation.h"
#include "Utils.h"
#include <iostream>
#include <unordered_map>
#include <vector>
#include <set>


void CGasTransportingNetwork::showConnection(const std::unordered_map<uint32_t, CPipe>& mP, const std::unordered_map<uint32_t, CStation>& mS)
{
    uint8_t flag = 0;
    if (mP.size() > 0 && mS.size() > 1)
    {
        for (auto& [i, p] : mP)
        {
            if (p.linked())
                p.showLink();
            flag += i;
        }
        if (flag==0)
            std::cout << "There are no pipes with connections!" << std::endl;
    }
    else
        std::cout << "There are no pipes or stations!" << std::endl;
}

void CGasTransportingNetwork::addConnection(std::unordered_map<uint32_t, CPipe>& mP, std::unordered_map<uint32_t, CStation>& mS)
{
    if ((mP.size() > 0) && (mS.size() > 1))
    {
        std::vector<uint32_t> result{};
        std::cout << "Enter pipe diameter to add connection: ";
        double_t pDiameter = getCorrectPipeDiameter();

        for (auto& [pID, p] : mP)
        {
            if (checkByDiameter(p, pDiameter))
            {
                result.push_back(p.getPipeID());
            }
        }

        uint32_t pipeId;

        if (result.empty())
        {
            std::cout << "There are no avaiable pipes with this parameter\n";
            CPipe pipe;
            std::cin >> pipe;
            mP.insert({ pipe.getPipeID(), pipe });
           pipeId = mP[1].newPipeID;
        }
        
        if (!result.empty())
        {
            pipeId = result[0];
        }

        std::cout << "Enter station id OUT: " << std::endl;
        uint32_t out = SearchId(mS, getCorrect(out));
        std::cout << "Enter station id IN: " << std::endl;
        uint32_t in = SearchId(mS, getCorrect(in));

        if (mP[pipeId].inStationID == 0 && mP[pipeId].outStationID == 0 && out != -1 && in != -1 && out != in)
        {
            mP[pipeId].link(in, out);
            mS[in].createLink();
            mS[out].createLink();
        }
        else
        {
            std::cout << "Error! Pipe already connected!";
        }
    }
    else
    {
        std::cout << "Not enough pipes or stations to connect\n";
    }
}

void CGasTransportingNetwork::deleteConnection(std::unordered_map<uint32_t, CPipe>& mP, std::unordered_map<uint32_t, CStation>& mS)
{
    if (mP.size() > 0 && mS.size() > 1)
    {
        std::cout << "Enter pipe id: " << std::endl;
        uint32_t pipeId = SearchId(mP, getCorrect(pipeId));
        if (pipeId != -1 && mP[pipeId].linked())
        {
            mP[pipeId].clearLink();
            mS[mP[pipeId].inStationID].clearLink();
            mS[mP[pipeId].outStationID].clearLink();
            std::cout << "Pipe and stations are disconnected!\n";
        }
        else
            std::cout << "There are no pipes with this id or pipe isn't connected" << std::endl;
    }
    else
        std::cout << "There are no pipes or stations!" << std::endl;
}

std::unordered_map<uint32_t, uint32_t> CGasTransportingNetwork::createIndexOfVertices(const std::unordered_map<uint32_t, CPipe>& mP, std::unordered_map<uint32_t, CStation>& mS)
{
    std::set<uint32_t> vertices;
    for (const auto& [i, p] : mP)
        if (p.canBeUsed() && mS.count(p.inStationID) && mS.count(p.outStationID))
        {
            vertices.insert(p.outStationID);
            vertices.insert(p.inStationID);
        }

    std::unordered_map<uint32_t, uint32_t> verticesIndex;
    uint32_t i = 0;
    for (const uint32_t& v : vertices)
        verticesIndex.insert({ v, i++ });


    return verticesIndex;
}

std::unordered_map<uint32_t, uint32_t> CGasTransportingNetwork::createIndexOfVerticesReverse(const std::unordered_map<uint32_t, CPipe>& mP, std::unordered_map<uint32_t, CStation>& mS)
{
    std::set<uint32_t> vertices;
    for (const auto& [i, p] : mP)
        if (p.canBeUsed() && mS.count(p.inStationID) && mS.count(p.outStationID))
        {
            vertices.insert(p.outStationID);
            vertices.insert(p.inStationID);
        }
    std::unordered_map<uint32_t, uint32_t> verticesIndex;
    uint32_t i = 0;
    for (const uint32_t& v : vertices)
        verticesIndex.insert({ i++, v });

    return verticesIndex;
}

std::vector<std::vector<uint32_t>> CGasTransportingNetwork::createGraph(const std::unordered_map<uint32_t, CPipe>& mP, std::unordered_map<uint32_t, CStation>& mS)
{
    std::unordered_map<uint32_t, uint32_t> verticesIndex = createIndexOfVertices(mP, mS);
    std::vector<std::vector<uint32_t>> result;
    result.resize(verticesIndex.size());
    for (const auto& [i, p] : mP)
        if (p.canBeUsed())
            result[verticesIndex[p.outStationID]].push_back(verticesIndex[p.inStationID]);

    return result;
}

std::vector<std::vector<double>> CGasTransportingNetwork::createMatrixWeights(const std::unordered_map<uint32_t, CPipe>& mP, std::unordered_map<uint32_t, CStation>& mS)
{
    std::unordered_map<uint32_t, uint32_t> verticesIndex = createIndexOfVertices(mP, mS);
    std::vector<std::vector<double>> weights;
    weights.assign(verticesIndex.size(), {});
    for (uint32_t i = 0; i < verticesIndex.size(); ++i)
    {
        weights[i].assign(verticesIndex.size(), INT_MAX);
        weights[i][i] = 0;
    }
    for (const auto& [i, p] : mP)
        if (p.canBeUsed())
            weights[verticesIndex[p.outStationID]][verticesIndex[p.inStationID]] = p.length;
    
    return weights;
}

std::vector<std::vector<uint32_t>> CGasTransportingNetwork::createMatrixThroughput(const std::unordered_map<uint32_t, CPipe>& mP, std::unordered_map<uint32_t, CStation>& mS)
{
    std::unordered_map<uint32_t, uint32_t> verticesIndex = createIndexOfVertices(mP, mS);
    std::vector<std::vector<uint32_t>> throughput;
    throughput.assign(verticesIndex.size(), {});
    for (int i = 0; i < verticesIndex.size(); ++i)
        throughput[i].assign(verticesIndex.size(), 0);
    for (const auto& [i, p] : mP)
        if (p.canBeUsed())
            throughput[verticesIndex[p.outStationID]][verticesIndex[p.inStationID]] = p.getProductivity();
    
    return throughput;
}









bool checkByDiameter(const CPipe& p, double parameter)
{
    return p.diameter == parameter;
}




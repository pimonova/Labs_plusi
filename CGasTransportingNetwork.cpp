#pragma once
#include "CGasTransportingNetwork.h"
#include "Cpipe.h"
#include "CStation.h"
#include "Utils.h"
#include <iostream>
#include <unordered_map>
#include <vector>



void CGasTransportingNetwork::showConnection(const std::unordered_map<uint32_t, CPipe>& mP, const std::unordered_map<uint32_t, CStation>& mS)
{
    if (mP.size() > 0 && mS.size() > 1)
    {
        for (auto& [i, p] : mP)
            if (p.linked())
                p.showLink();
    }
    else
        std::cout << "There are no pipes or stations!" << std::endl;
}

void CGasTransportingNetwork::addConnection(std::unordered_map<uint32_t, CPipe>&, std::unordered_map<uint32_t, CStation>&)
{

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
            std::cout << "Pipe and stations are disconnected!\n";
        }
        else
            std::cout << "There are no pipes with this id or pipe isn't connected" << std::endl;
    }
    else
        std::cout << "There are no pipes or stations!" << std::endl;
}


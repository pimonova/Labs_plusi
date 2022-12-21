#pragma once
#include <iostream>
#include <cstdint>
#include "CPipe.h"

// функции для проверки
template <typename T>
T getCorrect(T& x)
{
    while ((std::cin >> x).fail() || x <= 0)
    {
        std::cout << "Try again: ";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
    return x;
}

uint32_t getInRange(uint32_t x1, uint32_t x2);

double_t getCorrectPipeDiameter();

//поиск объектов

template<typename T>
uint32_t SearchId(const T& map, uint32_t id)
{
    if (map.find(id) != map.end()) return id;
    return -1;
}
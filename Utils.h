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

void getCorrectPipeDiameter(CPipe& p);
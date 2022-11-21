#include "CPipe.h"
#include <iostream>
#include "Utils.h"

uint32_t CPipe::newPipeID = 0;

std::istream& operator >> (std::istream& in, CPipe& x)
{
    std::cout << "Add pipe parameters: length, diameter, repair\n";
    std::cout << "Length:\n";
    getCorrect(x.length);
    std::cout << "Diameter:\n";
    getCorrect(x.diameter);
    std::cout << "Repair:\n";
    x.repair = getInRange(0, 1);
    return in;
}

std::ostream& operator << (std::ostream& out, const CPipe& x)
{
    out << "Pipe:\n";
    out << "ID: " << x.pipeID << " Length: " << x.length
        << " Diameter: "<< x.diameter << " Repair: " << x.repair << std::endl;
    return out;
}

CPipe::CPipe()
{
    pipeID = ++newPipeID;
    length = 10.0;
    diameter = 5.0;
    repair = 0;
}

uint32_t CPipe::getPipeID() const
{
    return pipeID;
}

#pragma once
#include <cstdint>
#include <iostream>

class CPipe
{
	uint32_t pipeID;
public:	

	static uint32_t newPipeID;

	double length, diameter;
	uint32_t repair;

	friend std::ostream& operator << (std::ostream& out, const CPipe& x);
	friend std::istream& operator >> (std::istream& in, CPipe& x);

	CPipe();

	uint32_t getPipeID() const;
};
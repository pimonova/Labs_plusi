#pragma once
#include <cstdint>
#include <string>

class CStation
{
	uint32_t stationID;
public:

	static uint32_t newStationID;

	std::string name;
	uint32_t numOfWorkshops, numOfWorkingWorkshops, efficiency;

	friend std::ostream& operator << (std::ostream& out, const CStation& x);
	friend std::istream& operator >> (std::istream& in, CStation& x);
	//friend std::ofstream& operator << (std::ofstream& out, const CStation& x);

	CStation();

	uint32_t getStationID();
	void setStationID(uint32_t);
};


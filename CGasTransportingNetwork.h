#pragma once
class CGasTransportingNetwork
{

public:
	void showConnection(const std::unordered_map<uint32_t, CPipe>&, const std::unordered_map<uint32_t, CStation>&);

	void addConnection(std::unordered_map<uint32_t, CPipe>&, std::unordered_map<uint32_t, CStation>&);

	void deleteConnection(std::unordered_map<uint32_t, CPipe>&, std::unordered_map<uint32_t, CStation>&);

};

template<typename T>
uint32_t SearchId(const T& map, uint32_t id)
{
	if (map.find(id) != map.end()) return id;
	return -1;
}

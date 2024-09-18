
#include "Bus.hpp"

#include <algorithm>

#include "challenges/2019/intcode/components/BusClient.hpp"

using namespace aoc::challenges::intcode2019;

void Bus::ReadData(address_t const address, data_t& outData)
{
    for (BusClient* client : m_connectedClients)
    {
        client->ReadData(address, outData);
    }
}

void Bus::WriteData(address_t const address, data_t const data)
{
    for (BusClient* client : m_connectedClients)
    {
        client->WriteData(address, data);
    }
}

void Bus::ConnectClient(BusClient* client)
{
    m_connectedClients.push_back(client);
}

void Bus::DisconnectClient(BusClient* client)
{
    std::remove(std::begin(m_connectedClients), std::end(m_connectedClients), client);
}

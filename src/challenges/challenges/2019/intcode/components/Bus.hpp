
#pragma once

#include <vector>

#include "challenges/2019/intcode/CommonDefinitions.hpp"

namespace aoc::challenges::intcode2019
{
    class BusClient;

    class Bus
    {
        std::vector<BusClient*> m_connectedClients;

    public:
        void Reset();
        bool ReadData(address_t const address, data_t& outData);
        void WriteData(address_t const address, data_t const data);

        void ConnectClient(BusClient* client);
        void DisconnectClient(BusClient* client);
    };
}
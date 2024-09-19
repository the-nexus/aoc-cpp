
#pragma once

#include "challenges/2019/intcode/CommonDefinitions.hpp"

namespace aoc::challenges::intcode2019
{
    class BusClient
    {
    public:
        virtual ~BusClient() = default;
        virtual void Reset() = 0;
        virtual bool ReadData(address_t const address, data_t& outData) = 0;
        virtual void WriteData(address_t const address, data_t const data) = 0;
    };
}

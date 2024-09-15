
#pragma once

#include <string>
#include <vector>

#include "challenges/2019/intcode/components/Memory.hpp"
#include "challenges/2019/intcode/components/Processor.hpp"

namespace aoc::challenges::intcode2019
{
    class Computer
    {
        Processor m_processor;
        Memory m_heapMemory;

    public:
        Computer(std::string const& programStr);

        void Reset();
        void Step();

        bool WriteData(size_t const address, int const data);
        bool ReadData(size_t const address, int& outData);
    };
}

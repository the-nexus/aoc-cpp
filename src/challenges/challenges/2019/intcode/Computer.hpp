
#pragma once

#include <string>
#include <vector>

#include "challenges/2019/intcode/components/Processor.hpp"

namespace aoc::challenges::intcode2019
{
    class Computer
    {
        Processor m_processor;
        std::vector<int> m_memory;
        std::vector<int> m_programData;

    public:
        Computer(std::string const& programStr);

        void Reset();
        void Step();

        bool WriteData(size_t const address, int const data);
        bool ReadData(size_t const address, int& outData);
    };
}


#pragma once

#include <string>
#include <vector>

#include "challenges/2019/intcode/components/Bus.hpp"
#include "challenges/2019/intcode/components/IODevice.hpp"
#include "challenges/2019/intcode/components/Memory.hpp"
#include "challenges/2019/intcode/components/Processor.hpp"

namespace aoc::challenges::intcode2019
{
    class Computer
    {
        Bus m_bus;
        Memory m_memory;
        IODevice m_ioDevice;
        Processor m_processor;
        std::vector<int> m_programData;

    public:
        Computer(std::string const& programStr);

        void WriteData(int const address, int const data);
        void ReadData(int const address, int& outData);

        void PushInputData(int const data);
        std::optional<int> PopOutputData();

        void Reset();
        void Step();

        bool HasHalted() const { return m_processor.HasHalted(); }
    };
}

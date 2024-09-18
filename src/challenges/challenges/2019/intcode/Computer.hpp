
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

        void WriteData(address_t const address, data_t const data);
        void ReadData(address_t const address, data_t& outData);

        void PushInputData(data_t const data);
        std::optional<data_t> PopOutputData();

        void Reset();
        void Step();

        bool HasHalted() const { return m_processor.HasHalted(); }
    };
}

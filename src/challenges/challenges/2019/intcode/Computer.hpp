
#pragma once

#include <string>
#include <vector>

#include "challenges/2019/intcode/components/Bus.hpp"
#include "challenges/2019/intcode/components/IOPort.hpp"
#include "challenges/2019/intcode/components/Memory.hpp"
#include "challenges/2019/intcode/components/Processor.hpp"

namespace aoc::challenges::intcode2019
{
    class IOPipe;

    class Computer
    {
        Bus m_bus;
        Memory m_memory;
        IOPort m_ioPort;
        Processor m_processor;
        std::vector<data_t> m_programData;

    public:
        static std::vector<data_t> CompileProgram(std::string const& programStr);

        Computer(std::vector<data_t> const& programData);
        ~Computer();

        void Reset();
        void Step();

        void WriteData(address_t const address, data_t const data);
        void ReadData(address_t const address, data_t& outData);

        void SetInputPipe(IOPipe* inputPipe);
        void SetOutputPipe(IOPipe* outputPipe);

        bool HasHalted() const { return m_processor.HasHalted(); }
    };
}

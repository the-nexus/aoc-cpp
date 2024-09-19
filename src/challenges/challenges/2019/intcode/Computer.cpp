
#include "Computer.hpp"

#include <algorithm>

#include "challenges/2019/intcode/io/IOPipe.hpp"

using namespace aoc::challenges::intcode2019;

std::vector<data_t> Computer::CompileProgram(std::string const& programStr)
{
    if (programStr.empty())
    {
        return {};
    }

    std::vector<data_t> programData;

    size_t const separatorCount = std::count_if(
        std::cbegin(programStr),
        std::cend(programStr),
        [](char const c) { return c == ','; });

    programData.resize(separatorCount + 1u);

    auto intcodeIt = std::begin(programData);
    data_t signMultiplier = 1;

    for (char const c : programStr)
    {
        if (c == ',')
        {
            ++intcodeIt;
            signMultiplier = 1;
            continue;
        }

        if (c == '-')
        {
            signMultiplier = -1;
            continue;
        }

        data_t const digit = static_cast<data_t>(c - '0');
        (*intcodeIt) = (*intcodeIt) * 10 + digit * signMultiplier;
    }

    return programData;
}

Computer::Computer(std::vector<data_t> const& programData)
    : m_programData(programData)
{
    m_memory.Resize(m_programData.size());
    m_memory.Flash(m_programData);
    m_bus.ConnectClient(&m_memory);

    address_t const ioPortAddress = static_cast<address_t>(m_memory.GetSize() + 1);
    m_ioPort.SetAddress(ioPortAddress);
    m_bus.ConnectClient(&m_ioPort);

    m_processor.SetDataBus(&m_bus);
    m_processor.SetIOPortAddress(ioPortAddress);
}

Computer::~Computer()
{
    m_processor.SetDataBus(nullptr);

    m_bus.DisconnectClient(&m_memory);
    m_bus.DisconnectClient(&m_ioPort);

    m_ioPort.SetInputPipe(nullptr);
    m_ioPort.SetOutputPipe(nullptr);
}

void Computer::Reset()
{
    m_processor.Reset();
    m_memory.Flash(m_programData);
}

void Computer::Step()
{
    m_processor.Step();
}

void Computer::WriteData(address_t const address, data_t const data)
{
    m_memory.WriteData(address, data);
}

void Computer::ReadData(address_t const address, data_t& outData)
{
    m_memory.ReadData(address, outData);
}

void Computer::SetInputPipe(IOPipe* inputPipe)
{
    m_ioPort.SetInputPipe(inputPipe);
}

void Computer::SetOutputPipe(IOPipe* outputPipe)
{
    m_ioPort.SetOutputPipe(outputPipe);
}

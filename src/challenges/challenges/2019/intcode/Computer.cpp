
#include "Computer.hpp"

#include <algorithm>

using namespace aoc::challenges::intcode2019;

Computer::Computer(std::string const& programStr)
{
    if (programStr.empty())
    {
        // Nothing to parse
        return;
    }

    size_t const separatorCount = std::count_if(
        std::cbegin(programStr),
        std::cend(programStr),
        [](char const c) { return c == ','; });

    m_programData.resize(separatorCount + 1u);

    auto intcodeIt = std::begin(m_programData);
    int signMultiplier = 1;

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

        int const digit = static_cast<int>(c - '0');
        (*intcodeIt) = (*intcodeIt) * 10 + digit * signMultiplier;
    }

    m_memory = { m_programData.size() };
    m_memory.Flash(m_programData);
    m_bus.ConnectSerialDevice(&m_memory);

    m_ioDevice.SetAddress(static_cast<int>(m_memory.GetSize()) + 1);
    m_bus.ConnectSerialDevice(&m_ioDevice);

    m_processor.SetSerialDevice(&m_bus);
    m_processor.SetIOAddress(m_ioDevice.GetAddress());
}

void Computer::WriteData(int const address, int const data)
{
    m_memory.WriteData(address, data);
}

void Computer::ReadData(int const address, int& outData)
{
    m_memory.ReadData(address, outData);
}

void Computer::PushInputData(int const data) 
{
    m_ioDevice.PushInputData(data);
}

std::optional<int> Computer::PopOutputData()
{
    return m_ioDevice.PopOutputData();
}

void Computer::Reset()
{
    m_processor.Reset();
    m_ioDevice.Reset();
    m_memory.Flash(m_programData);
}

void Computer::Step()
{
    m_processor.Step();
}

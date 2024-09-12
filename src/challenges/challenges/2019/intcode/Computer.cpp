
#include "Computer.hpp"

using namespace aoc::challenges::intcode2019;

Computer::Computer(std::string const& programStr)
{

}

void Computer::Reset()
{
    m_processor.Reset();
    std::copy(std::begin(m_programData), std::end(m_programData), std::begin(m_memory))
}

void Computer::Step()
{
    m_processor.Step();
}

bool Computer::WriteData(size_t const address, int const data)
{
    if (address >= m_memory.size())
    {
        return false;
    }

    m_memory[address] = data;
    return true;
}

bool Computer::ReadData(size_t const address, int& outData)
{
    if (address >= m_memory.size())
    {
        return false;
    }

    outData = m_memory[address];
    return true;
}
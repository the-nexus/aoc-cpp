
#include "Memory.hpp"

using namespace aoc::challenges::intcode2019;

Memory::Memory(size_t const size)
    : m_data(size)
{
    Format();
}

void Memory::ReadData(address_t const address, data_t& outData)
{
    if (address < 0 || address >= static_cast<address_t>(m_data.size()))
    {
        return;
    }

    outData = m_data[address];
}

void Memory::WriteData(address_t const address, data_t const data)
{
    if (address < 0 || address >= static_cast<address_t>(m_data.size()))
    {
        return;
    }

    m_data[address] = data;
}

void Memory::Format()
{
    std::fill(std::begin(m_data), std::end(m_data), 0);
}

void Memory::Flash(std::vector<data_t> const& data)
{
    std::copy(std::begin(data), std::end(data), std::begin(m_data));
}

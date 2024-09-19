
#include "Memory.hpp"

using namespace aoc::challenges::intcode2019;

Memory::Memory(size_t const size)
    : m_data(size)
{}

bool Memory::ReadData(address_t const address, data_t& outData)
{
    if (address < 0 || address >= static_cast<address_t>(m_data.size()))
    {
        return false;
    }

    outData = m_data[address];
    return true;
}

void Memory::WriteData(address_t const address, data_t const data)
{
    if (address < 0 || address >= static_cast<address_t>(m_data.size()))
    {
        return;
    }

    m_data[address] = data;
}

void Memory::Resize(size_t const size)
{
    m_data.resize(size);
}

void Memory::Flash(std::vector<data_t> const& data)
{
    std::copy(std::begin(data), std::end(data), std::begin(m_data));
}

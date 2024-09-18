
#include "IODevice.hpp"

using namespace aoc::challenges::intcode2019;

void IODevice::ReadData(address_t const address, data_t& outData)
{
    if (address != m_address)
    {
        return;
    }

    outData = m_inputQueue.front();
    m_inputQueue.pop_front();
}

void IODevice::WriteData(address_t const address, data_t const data)
{
    if (address != m_address)
    {
        return;
    }

    m_outputQueue.push_back(data);
}

void IODevice::PushInputData(data_t const data)
{
    m_inputQueue.push_back(data);
}

std::optional<data_t> IODevice::PopOutputData()
{
    if (m_outputQueue.empty())
    {
        return std::nullopt;
    }

    data_t const data = m_outputQueue.front();
    m_outputQueue.pop_front();

    return std::make_optional(data);
}

void IODevice::Reset()
{
    m_inputQueue.clear();
    m_outputQueue.clear();
}

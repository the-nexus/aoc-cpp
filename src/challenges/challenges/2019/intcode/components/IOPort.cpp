
#include "IOPort.hpp"

#include "challenges/2019/intcode/io/IOPipe.hpp"

using namespace aoc::challenges::intcode2019;

void IOPort::Reset()
{
    if (m_inputPipe)
    {
        m_inputPipe->Reset();
    }

    if (m_outputPipe)
    {
        m_outputPipe->Reset();
    }
}

bool IOPort::ReadData(address_t const address, data_t& outData)
{
    if (address != m_address)
    {
        return false;
    }

    if (!m_inputPipe)
    {
        return false;
    }

    return m_inputPipe->ReadData(outData);
}

void IOPort::WriteData(address_t const address, data_t const data)
{
    if (address != m_address)
    {
        return;
    }

    if (!m_outputPipe)
    {
        return;
    }

    m_outputPipe->WriteData(data);
}

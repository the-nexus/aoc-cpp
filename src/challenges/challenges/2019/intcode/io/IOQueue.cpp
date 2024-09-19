
#include "IOQueue.hpp"

using namespace aoc::challenges::intcode2019;

void IOQueue::Reset()
{
    m_dataQueue.clear();
}

bool IOQueue::ReadData(data_t& outData)
{
    if (m_dataQueue.empty())
    {
        return false;
    }

    outData = m_dataQueue.front();
    m_dataQueue.pop_front();
    return true;
}

void IOQueue::WriteData(data_t const data)
{
    m_dataQueue.push_back(data);
}

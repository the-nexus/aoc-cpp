
#include "Bus.hpp"

#include <algorithm>

using namespace aoc::challenges::intcode2019;

void Bus::ReadData(int const address, int& outData)
{
    for (ISerialPort* serialDevice : m_connectedSerialDevices)
    {
        serialDevice->ReadData(address, outData);
    }
}

void Bus::WriteData(int const address, int const data)
{
    for (ISerialPort* serialDevice : m_connectedSerialDevices)
    {
        serialDevice->WriteData(address, data);
    }
}

void Bus::ConnectSerialDevice(ISerialPort* serialDevice)
{
    m_connectedSerialDevices.push_back(serialDevice);
}

void Bus::DisconnectSerialDevice(ISerialPort* serialDevice)
{
    std::remove(std::begin(m_connectedSerialDevices), std::end(m_connectedSerialDevices), serialDevice);
}


#pragma once

#include <vector>

#include "challenges/2019/intcode/components/ISerialPort.hpp"

namespace aoc::challenges::intcode2019
{
    class Bus final : public ISerialPort
    {
        std::vector<ISerialPort*> m_connectedSerialDevices;

    public:
        void ReadData(int const address, int& outData) override;
        void WriteData(int const address, int const data) override;

        void ConnectSerialDevice(ISerialPort* serialDevice);
        void DisconnectSerialDevice(ISerialPort* serialDevice);
    };
}

#pragma once

#include <vector>

#include "challenges/2019/intcode/components/SerialPort.hpp"

namespace aoc::challenges::intcode2019
{
    template <typename address_t, typename data_t>
    class Bus : public SerialPort<address_t, data_t>
    {
        std::vector<SerialPort<address_t, data_t>*> m_connectedSerialDevices;

    public:
        void ConnectSerialDevice(SerialPort<address_t, data_t>* serialDevice);
        void DisconnectSerialDevice(SerialPort<address_t, data_t>* serialDevice)
    };
}
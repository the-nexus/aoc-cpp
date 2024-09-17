
#pragma once

namespace aoc::challenges::intcode2019
{
    class ISerialPort
    {
    public:
        virtual void ReadData(int const address, int& outData) = 0;
        virtual void WriteData(int const address, int const data) = 0;
    };
}


#pragma once

#include "challenges/2019/intcode/components/ISerialPort.hpp"

namespace aoc::challenges::intcode2019
{
    class Processor
    {
        ISerialPort* m_serialDevice = nullptr;
        int m_ioAddress = 0;
        int m_programCounter = 0;
        int m_instruction = 0;
        bool m_hasHalted = false;

    public:
        void SetSerialDevice(ISerialPort* serialDevice) { m_serialDevice = serialDevice; }
        void SetIOAddress(int const ioAddress) { m_ioAddress = ioAddress; }

        bool HasHalted() const { return m_hasHalted; }

        void Reset();
        void Step();

    private:
        void Add();
        void Multiply();
        void Input();
        void Output();
        void Halt();

        int GetOpcode() const;
        int GetParameterMode(int const parameterOffset) const;
        int GetParameterAddress(int const parameterOffset) const;
    };
}

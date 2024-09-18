
#pragma once

#include "challenges/2019/intcode/components/Bus.hpp"

namespace aoc::challenges::intcode2019
{
    class Processor
    {
        Bus* m_dataBus = nullptr;
        address_t m_ioAddress = 0;
        address_t m_instructionPointer = 0;
        data_t m_instruction = 0;
        bool m_hasHalted = false;

    public:
        void SetDataBus(Bus* dataBus) { m_dataBus = dataBus; }
        void SetIOAddress(address_t const ioAddress) { m_ioAddress = ioAddress; }

        bool HasHalted() const { return m_hasHalted; }

        void Reset();
        void Step();

    private:
        void Add();
        void Multiply();
        void Input();
        void Output();
        void JumpIfNotZero();
        void JumpIfZero();
        void CompareLess();
        void CompareEqual();
        void Halt();

        data_t GetOpcode() const;
        data_t GetParameterMode(data_t const parameterOffset) const;
        address_t GetParameterAddress(data_t const parameterOffset) const;
        address_t AddressModePosition(data_t parameterOffset) const;
        address_t AddressModeImmediate(data_t parameterOffset) const;
    };
}

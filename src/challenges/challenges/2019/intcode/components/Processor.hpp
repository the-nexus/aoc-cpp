
#pragma once

#include "challenges/2019/intcode/components/Bus.hpp"

namespace aoc::challenges::intcode2019
{
    class Processor
    {
        Bus* m_dataBus = nullptr;
        address_t m_ioPortAddress = 0;
        address_t m_instructionPointer = 0;
        data_t m_instruction = 0;
        bool m_hasHalted = false;

    public:
        void Reset();
        void Step();

        void SetDataBus(Bus* dataBus) { m_dataBus = dataBus; }
        void SetIOPortAddress(address_t const ioPortAddress) { m_ioPortAddress = ioPortAddress; }

        bool HasHalted() const { return m_hasHalted; }

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

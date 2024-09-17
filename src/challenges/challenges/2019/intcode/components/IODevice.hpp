
#pragma once

#include <deque>
#include <optional>

#include "challenges/2019/intcode/components/ISerialPort.hpp"

namespace aoc::challenges::intcode2019
{
    class IODevice final : public ISerialPort
    {
        std::deque<int> m_inputQueue;
        std::deque<int> m_outputQueue;
        int m_address = 0;

    public:

        void ReadData(int const address, int& outData) override;
        void WriteData(int const address, int const data) override;

        void PushInputData(int const data);
        std::optional<int> PopOutputData();

        void Reset();

        void SetAddress(int const address) { m_address = address; }
        int GetAddress() const { return m_address; }
    };
}
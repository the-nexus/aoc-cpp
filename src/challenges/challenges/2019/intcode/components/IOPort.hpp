
#pragma once

#include <deque>
#include <optional>

#include "challenges/2019/intcode/components/BusClient.hpp"

namespace aoc::challenges::intcode2019
{
    class IOPipe;

    class IOPort final : public BusClient
    {
        address_t m_address = 0;
        IOPipe* m_inputPipe = nullptr;
        IOPipe* m_outputPipe = nullptr;

    public:
        void Reset() override;
        bool ReadData(address_t const address, data_t& outData) override;
        void WriteData(address_t const address, data_t const data) override;

        void SetAddress(address_t const address) { m_address = address; }
        void SetInputPipe(IOPipe* inputPipe) { m_inputPipe = inputPipe; }
        void SetOutputPipe(IOPipe* outputPipe) { m_outputPipe = outputPipe; }

        address_t GetAddress() const { return m_address; }
    };
}
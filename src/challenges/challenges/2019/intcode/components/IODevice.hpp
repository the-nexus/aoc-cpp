
#pragma once

#include <deque>
#include <optional>

#include "challenges/2019/intcode/components/BusClient.hpp"

namespace aoc::challenges::intcode2019
{
    class IODevice final : public BusClient
    {
        std::deque<data_t> m_inputQueue;
        std::deque<data_t> m_outputQueue;
        address_t m_address = 0;

    public:

        void ReadData(address_t const address, data_t& outData) override;
        void WriteData(address_t const address, data_t const data) override;

        void PushInputData(data_t const data);
        std::optional<data_t> PopOutputData();

        void Reset();

        void SetAddress(address_t const address) { m_address = address; }
        address_t GetAddress() const { return m_address; }
    };
}
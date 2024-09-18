
#pragma once

#include <algorithm>
#include <memory>
#include <vector>

#include "challenges/2019/intcode/components/BusClient.hpp"

namespace aoc::challenges::intcode2019
{
    class Memory final : public BusClient
    {
        std::vector<data_t> m_data;

    public:
        Memory() = default;
        Memory(size_t const size);

        size_t GetSize() const { return m_data.size(); }

        void ReadData(address_t const address, data_t& outData) override;
        void WriteData(address_t const address, data_t const data) override;

        void Format();
        void Flash(std::vector<data_t> const& data);
    };
}

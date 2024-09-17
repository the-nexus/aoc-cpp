
#pragma once

#include <algorithm>
#include <memory>
#include <vector>

#include "challenges/2019/intcode/components/ISerialPort.hpp"

namespace aoc::challenges::intcode2019
{
    class Memory final : public ISerialPort
    {
        std::vector<int> m_data;

    public:
        Memory() = default;
        Memory(size_t const size);

        size_t GetSize() const { return m_data.size(); }

        void ReadData(int const address, int& outData) override;
        void WriteData(int const address, int const data) override;

        void Format();
        void Flash(std::vector<int> const& data);
    };
}

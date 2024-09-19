
#pragma once

#include <deque>

#include "challenges/2019/intcode/io/IOPipe.hpp"

namespace aoc::challenges::intcode2019
{
    class IOQueue final : public IOPipe
    {
        std::deque<data_t> m_dataQueue;

    public:
        void Reset() override;
        bool ReadData(data_t& outData) override;
        void WriteData(data_t const data) override;
    };
}

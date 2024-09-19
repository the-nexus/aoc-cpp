
#pragma once

#include "challenges/2019/intcode/CommonDefinitions.hpp"

namespace aoc::challenges::intcode2019
{
    class IOPipe
    {
    public:
        virtual ~IOPipe() = default;
        virtual void Reset() = 0;
        virtual bool ReadData(data_t& outData) = 0;
        virtual void WriteData(data_t const data) = 0;
    };
}
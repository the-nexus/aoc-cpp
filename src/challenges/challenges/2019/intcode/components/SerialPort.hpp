
#pragma once

#include <limits>
#include <tuple>

namespace aoc::challenges::intcode2019
{
    class SerialPort
    {
        std::pair<int, int> m_addressRange = { std::numeric_limits<int>::min(), std::numeric_limits<int>::max() };
        bool m_isReadable = true;
        bool m_isWritable = true;

    public:
        SerialPort(bool const isReadable, bool const isWritable);
        SerialPort(bool const isReadable, bool const isWritable, std::pair<int, int> const& addressRange);

        bool IsReadable() const { return m_isReadable; }
        bool IsWritable() const { return m_isWritable; }

        virtual bool ReadData(int const address, int& outData) const = 0;
        virtual bool WriteData(int const address, int const data) = 0;
    }
}

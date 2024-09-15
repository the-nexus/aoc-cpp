
#include "SerialPort.hpp"

using namespace aoc::challenges::intcode2019;

SerialPort::SerialPort(bool const isReadable, bool const isWritable)
    : m_isReadable(isReadable)
    , m_isWritable(isWritable)
{}

SerialPort::SerialPort(bool const isReadable, bool const isWritable, std::pair<int, int> const& addressRange)
    : SerialPort(isReadable, isWritable)
    , m_addressRange(addressRange)
{}
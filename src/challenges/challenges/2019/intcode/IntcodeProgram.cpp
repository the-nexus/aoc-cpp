
#include "IntcodeProgram.hpp"

#include <algorithm>

using namespace aoc::challenges;

IntcodeProgram::IntcodeProgram(std::string const& initialMemory)
{
    if (initialMemory.empty())
    {
        // Nothing to parse
        return;
    }

    size_t const separatorCount = std::count_if(
        std::cbegin(initialMemory),
        std::cend(initialMemory),
        [](char const c) { return c == ','; });

    m_initialMemory.resize(separatorCount + 1u);

    auto intcodeIt = std::begin(m_initialMemory);
    intcode_t signMultiplier = 1;

    for (char const c : initialMemory)
    {
        if (c == ',')
        {
            ++intcodeIt;
            signMultiplier = 1;
            continue;
        }

        if (c == '-')
        {
            signMultiplier = -1;
            continue;
        }

        intcode_t const digit = static_cast<intcode_t>(c - '0');
        (*intcodeIt) = (*intcodeIt) * 10 + digit * signMultiplier;
    }

    m_memory.resize(m_initialMemory.size());
    std::copy(std::begin(m_initialMemory), std::end(m_initialMemory), std::begin(m_memory));
}

void IntcodeProgram::SetAt(intcode_t const position, intcode_t const value)
{
    size_t const vectorizedPosition = static_cast<size_t>(position);
    if (vectorizedPosition >= m_memory.size())
    {
        // Position is out of bounds
        return;
    }

    m_memory[vectorizedPosition] = value;
}

intcode_t IntcodeProgram::GetAt(intcode_t const position) const
{
    size_t const vectorizedPosition = static_cast<size_t>(position);
    if (vectorizedPosition >= m_memory.size())
    {
        // Position is out of bounds
        return 0;
    }

    return m_memory[vectorizedPosition];
}

void IntcodeProgram::Reset()
{
    std::copy(std::begin(m_initialMemory), std::end(m_initialMemory), std::begin(m_memory));
    m_instructionPointer = 0;
}

bool IntcodeProgram::Step()
{
    if (m_instructionPointer >= m_memory.size())
    {
        return false;
    }

    intcode_t const opcode = m_memory[m_instructionPointer];

    switch (opcode)
    {
        case 1: // Numeral addition
            PerformAddition(
                m_memory[m_instructionPointer + 1],
                m_memory[m_instructionPointer + 2],
                m_memory[m_instructionPointer + 3]);
            m_instructionPointer += 4;
            break;

        case 2: // Numeral multiplication
            PerformMultiplication(
                m_memory[m_instructionPointer + 1],
                m_memory[m_instructionPointer + 2],
                m_memory[m_instructionPointer + 3]);
            m_instructionPointer += 4;
            break;

        case 99: // Halts program
            return false;

        default:
            m_instructionPointer += 4;
            break;
    }

    return true;
}

void IntcodeProgram::PerformAddition(intcode_t const inputA, intcode_t const inputB, intcode_t const output)
{
    m_memory[output] = m_memory[inputA] + m_memory[inputB];
}

void IntcodeProgram::PerformMultiplication(intcode_t const inputA, intcode_t const inputB, intcode_t const output)
{
    m_memory[output] = m_memory[inputA] * m_memory[inputB];
}

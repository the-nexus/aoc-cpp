
#pragma once

#include <string>
#include <vector>

namespace aoc::challenges
{
    typedef int intcode_t;

    class IntcodeProgram
    {
        std::vector<intcode_t> m_initialMemory;
        std::vector<intcode_t> m_memory;
        intcode_t m_instructionPointer = 0;

    public:
        IntcodeProgram(std::string const& program);
        intcode_t GetAt(intcode_t const position) const;
        void SetAt(intcode_t const position, intcode_t const value);
        void Reset();
        bool Step();

    private:
        void PerformAddition(intcode_t const inputA, intcode_t const inputB, intcode_t const output);
        void PerformMultiplication(intcode_t const inputA, intcode_t const inputB, intcode_t const output);
    };
}

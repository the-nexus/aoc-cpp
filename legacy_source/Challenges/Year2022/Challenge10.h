
#pragma once

#include "Challenges/ChallengeAbstract.h"

namespace AOC::Challenges::Year2022
{
    class Challenge10 final : public ChallengeAbstract
    {
    private:
        enum class EOperationType : int
        {
            NOOP = 1,
            ADDX = 2
        };

        std::vector<std::pair<EOperationType, int>> m_instructions;

    public:
        Challenge10(std::vector<std::string> const& inputLines)
        {
            m_instructions.resize(inputLines.size() + 1); // Everything initializes to defaults (NOOP, 0), so push back an extra default instruction to simplify execution
            for (size_t lineIndex = 0; lineIndex < inputLines.size(); ++lineIndex)
            {
                if (inputLines[lineIndex][0] == 'n')
                {
                    m_instructions[lineIndex].first = EOperationType::NOOP;
                    m_instructions[lineIndex].second = 0;
                }
                else
                {
                    m_instructions[lineIndex].first = EOperationType::ADDX;
                    m_instructions[lineIndex].second = atoi(inputLines[lineIndex].substr(5).c_str());
                }
            }
        }

        virtual void Run_PartOne() override
        {
            int xReg = 1;
            int delay = static_cast<int>(m_instructions[0].first);
            int instructionIndex = 0;
            int signalStrengthSum = 0;

            for (int cycle = 1; cycle <= 220; ++cycle)
            {
                if ((cycle - 20) % 40 == 0)
                {
                    int const signalStrength = cycle * xReg;
                    signalStrengthSum += signalStrength;
                }

                if (--delay == 0)
                {
                    xReg += m_instructions[instructionIndex].second;
                    delay = static_cast<int>(m_instructions[++instructionIndex].first);
                }
            }

            std::cout << signalStrengthSum << std::endl;
        }

        virtual void Run_PartTwo() override
        {
            int xReg = 1;
            int delay = static_cast<int>(m_instructions[0].first);
            int instructionIndex = 0;

            for (int cycle = 1; cycle <= 240; ++cycle)
            {
                int const xPos = cycle % 40;
                bool const isLitPixel = xPos >= xReg && xPos <= xReg + 2;
                std::cout << (isLitPixel ? '#' : ' ');

                if (--delay == 0)
                {
                    xReg += m_instructions[instructionIndex].second;
                    delay = static_cast<int>(m_instructions[++instructionIndex].first);
                }

                if (xPos == 0)
                {
                    std::cout << std::endl;
                }
            }
        }
    };
}

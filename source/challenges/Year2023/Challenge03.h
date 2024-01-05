#pragma once

#include "../ChallengeAbstract.h"

namespace Year2023
{
    class Challenge03 final : public ChallengeAbstract
    {
        std::vector<std::string> m_lines;

    public:
        Challenge03(std::vector<std::string> const& inputLines)
        {
            m_lines = inputLines;
        }

        virtual void Run_PartOne() override
        {
            int partSum = 0;

            for (size_t lineIndex = 0; lineIndex < m_lines.size(); ++lineIndex)
            {
                bool isPartNumber = false;
                int number = 0;

                for (size_t columnIndex = 0; columnIndex < m_lines[lineIndex].size(); ++columnIndex)
                {
                    char const symbol = m_lines[lineIndex][columnIndex];
                    if (IsNumberSymbol(symbol))
                    {
                        number = number * 10 + static_cast<int>(symbol - '0');
                        isPartNumber = isPartNumber || HasNeighbourPartSymbol(lineIndex, columnIndex);
                    }
                    else if (number != 0)
                    {
                        if (isPartNumber)
                        {
                            partSum += number;
                        }

                        number = 0;
                        isPartNumber = false;
                    }
                }

                if (number != 0 && isPartNumber)
                {
                    partSum += number;
                }
            }

            std::cout << partSum << std::endl;
        }

        virtual void Run_PartTwo() override
        {
            std::cout << "WARNING: Part Two Not Implemented" << std::endl;
        }

    private:
        static bool IsNumberSymbol(char const symbol)
        {
            return symbol >= '0' && symbol <= '9';
        }

        static bool IsPartSymbol(char const symbol)
        {
            if (symbol == '.')
            {
                return false;
            }

            if (IsNumberSymbol(symbol))
            {
                return false;
            }

            return true;
        }

        bool HasNeighbourPartSymbol(size_t const lineIndex, size_t const columnIndex) const
        {
            bool const checkUp = lineIndex > 0;
            bool const checkDown = lineIndex < m_lines.size() - 1;
            bool const checkLeft = columnIndex > 0;
            bool const checkRight = columnIndex < m_lines[lineIndex].size() - 1;

            if (checkUp)
            {
                if (IsPartSymbol(m_lines[lineIndex - 1][columnIndex]) ||
                    (checkLeft && IsPartSymbol(m_lines[lineIndex - 1][columnIndex - 1])) ||
                    (checkRight && IsPartSymbol(m_lines[lineIndex - 1][columnIndex + 1])))
                {
                    return true;
                }
            }

            // Check middle line
            {
                if ((checkLeft && IsPartSymbol(m_lines[lineIndex][columnIndex - 1])) ||
                    (checkRight && IsPartSymbol(m_lines[lineIndex][columnIndex + 1])))
                {
                    return true;
                }
            }

            if (checkDown)
            {
                if (IsPartSymbol(m_lines[lineIndex + 1][columnIndex]) ||
                    (checkLeft && IsPartSymbol(m_lines[lineIndex + 1][columnIndex - 1])) ||
                    (checkRight && IsPartSymbol(m_lines[lineIndex + 1][columnIndex + 1])))
                {
                    return true;
                }
            }

            return false;
        }
    };
}

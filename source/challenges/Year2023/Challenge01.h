#pragma once

#include "../ChallengeAbstract.h"

namespace Year2023
{
    class Challenge01 final : public ChallengeAbstract
    {
    private:
        std::vector<std::string> m_lines;

    public:
        Challenge01(std::vector<std::string> const& inputLines)
        {
            m_lines = inputLines;
        }

        virtual void Run_PartOne() override
        {
            int calibrationSum = 0;
            for (std::string const& line : m_lines)
            {
                calibrationSum += GetCalibrationValue(line, false);
            }

            std::cout << calibrationSum << std::endl;
        }

        virtual void Run_PartTwo() override
        {
            int calibrationSum = 0;
            for (std::string const& line : m_lines)
            {
                calibrationSum += GetCalibrationValue(line, true);
            }

            std::cout << calibrationSum << std::endl;
        }

    private:
        static int GetCalibrationValue(std::string const& line, bool const shouldConsiderWords)
        {
            int firstDigit = -1;
            int lastDigit = -1;

            for (size_t pos = 0; pos < line.size(); ++pos)
            {
                int const matchedDigit = GetMatchingDigit(line, pos, shouldConsiderWords);
                if (matchedDigit != -1)
                {
                    lastDigit = matchedDigit;
                    if (firstDigit == -1)
                    {
                        firstDigit = matchedDigit;
                    }
                }
            }

            return firstDigit * 10 + lastDigit;
        }

        static int GetMatchingDigit(std::string const& line, size_t const pos, bool const shouldConsiderWords)
        {
            if (line[pos] > '0' && line[pos] <= '9')
            {
                return static_cast<int>(line[pos] - '0');
            }

            if (shouldConsiderWords)
            {
                static std::string const one = "one";
                static std::string const two = "two";
                static std::string const three = "three";
                static std::string const four = "four";
                static std::string const five = "five";
                static std::string const six = "six";
                static std::string const seven = "seven";
                static std::string const eight = "eight";
                static std::string const nine = "nine";

                if (MatchesWord(one, line, pos)) return 1;
                if (MatchesWord(two, line, pos)) return 2;
                if (MatchesWord(three, line, pos)) return 3;
                if (MatchesWord(four, line, pos)) return 4;
                if (MatchesWord(five, line, pos)) return 5;
                if (MatchesWord(six, line, pos)) return 6;
                if (MatchesWord(seven, line, pos)) return 7;
                if (MatchesWord(eight, line, pos)) return 8;
                if (MatchesWord(nine, line, pos)) return 9;
            }

            return -1;
        }

        static bool MatchesWord(std::string const& word, std::string const& line, size_t const pos)
        {
            if (pos + word.size() > line.size())
            {
                return false;
            }

            for (size_t wordPos = 0; wordPos < word.size(); ++wordPos)
            {
                if (word[wordPos] != line[pos + wordPos])
                {
                    return false;
                }
            }

            return true;
        }
    };
}

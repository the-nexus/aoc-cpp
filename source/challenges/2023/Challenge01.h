#pragma once

#include "../ChallengeAbstract.h"

namespace Year2023
{
    class Challenge01 : public ChallengeAbstract
    {
    private:

        class LinearWordMatcher
        {
        private:
            std::string m_word;
            size_t m_position;

        public:
            LinearWordMatcher(std::string const& word)
                : m_word(word)
                , m_position(-1)
            {}

            bool Match(char const nextCharacter)
            {
                if (++m_position < m_word.size())
                {
                    if (m_word[m_position] == nextCharacter)
                    {
                        return m_position == m_word.size() - 1;
                    }
                }

                m_position = -1;
                return false;
            }

            void Reset()
            {
                m_position = -1;
            }
        };

        std::vector<std::string> m_lines;
        mutable std::vector<LinearWordMatcher> m_matchers;

    public:
        virtual void SetUp(std::vector<std::string> const& inputLines) override
        {
            m_lines = inputLines;

            m_matchers.reserve(10);
            m_matchers.emplace_back("zero");
            m_matchers.emplace_back("one");
            m_matchers.emplace_back("two");
            m_matchers.emplace_back("three");
            m_matchers.emplace_back("four");
            m_matchers.emplace_back("five");
            m_matchers.emplace_back("six");
            m_matchers.emplace_back("seven");
            m_matchers.emplace_back("eight");
            m_matchers.emplace_back("nine");
        }

        virtual void Run_PartOne() override
        {
            int calibrationSum = 0;
            for (std::string const& line : m_lines)
            {
                int const calibrationValue = GetCalibrationValue(line, false);
                if (calibrationValue != -1)
                {
                    calibrationSum += calibrationValue;
                }
            }

            std::cout << calibrationSum << std::endl;
        }

        virtual void Run_PartTwo() override
        {
            int calibrationSum = 0;
            for (std::string const& line : m_lines)
            {
                int const calibrationValue = GetCalibrationValue(line, true);
                if (calibrationValue != -1)
                {
                    calibrationSum += calibrationValue;
                }
            }

            std::cout << calibrationSum << std::endl;
        }

        virtual void CleanUp() override {}

        int GetCalibrationValue(std::string const& line, bool shouldConsiderWords) const
        {
            if (shouldConsiderWords)
            {
                for (LinearWordMatcher& matcher : m_matchers)
                {
                    matcher.Reset();
                }
            }

            int firstDigit = -1;
            int lastDigit = -1;

            for (auto it = line.cbegin(); it < line.cend(); ++it)
            {
                bool wasMatched = false;
                char const digitChar = *it;

                if (digitChar >= '0' && digitChar <= '9')
                {
                    wasMatched = true;
                    lastDigit = static_cast<int>(digitChar - '0');
                    if (firstDigit == -1)
                    {
                        firstDigit = lastDigit;
                    }
                }

                if (shouldConsiderWords)
                {
                    for (int digit = 0; digit < m_matchers.size(); ++digit)
                    {
                        if (m_matchers[digit].Match(digitChar))
                        {
                            wasMatched = true;
                            lastDigit = digit;
                            if (firstDigit == -1)
                            {
                                firstDigit = lastDigit;
                            }

                            break;
                        }
                    }

                    if (wasMatched)
                    {
                        for (LinearWordMatcher& matcher : m_matchers)
                        {
                            matcher.Reset();
                        }
                    }
                }
            }

            if (firstDigit == -1 || lastDigit == -1)
            {
                return -1;
            }
            else
            {
                return firstDigit * 10 + lastDigit;
            }
        }
    };
}

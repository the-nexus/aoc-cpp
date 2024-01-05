#pragma once

#include "../ChallengeAbstract.h"

namespace Year2022
{
    class Challenge04 : public ChallengeAbstract
    {
    private:
        typedef std::pair<int, int> SectionRange;
        std::vector<std::pair<SectionRange, SectionRange>> m_elfPairs;

    public:
        virtual void SetUp(std::vector<std::string> const& inputLines) override
        {
            m_elfPairs.resize(inputLines.size());
            for (size_t lineIndex = 0; lineIndex < inputLines.size(); ++lineIndex)
            {
                std::string const& inputLine = inputLines[lineIndex];

                size_t const elfDelimiterPos = inputLine.find_first_of(',');
                size_t const firstRangeDelimiterPos = inputLine.find_first_of('-');
                size_t const secondRangeDelimiterPos = inputLine.find_last_of('-');

                m_elfPairs[lineIndex].first.first = atoi(inputLine.substr(0, firstRangeDelimiterPos).c_str());
                m_elfPairs[lineIndex].first.second = atoi(inputLine.substr(firstRangeDelimiterPos + 1, elfDelimiterPos - firstRangeDelimiterPos - 1).c_str());
                m_elfPairs[lineIndex].second.first = atoi(inputLine.substr(elfDelimiterPos + 1, secondRangeDelimiterPos - elfDelimiterPos - 1).c_str());
                m_elfPairs[lineIndex].second.second = atoi(inputLine.substr(secondRangeDelimiterPos + 1, inputLine.size() - secondRangeDelimiterPos - 1).c_str());
            }
        }

        virtual void Run_PartOne() override
        {
            int fullyContainedRangeCount = 0;
            for (std::pair<SectionRange, SectionRange> const& elfPair : m_elfPairs)
            {
                if (IsRangeFullyContained(elfPair.first, elfPair.second) ||
                    IsRangeFullyContained(elfPair.second, elfPair.first))
                {
                    ++fullyContainedRangeCount;
                }
            }
            std::cout << fullyContainedRangeCount << std::endl;
        }

        virtual void Run_PartTwo() override
        {
            int intersectingRangeCount = 0;
            for (std::pair<SectionRange, SectionRange> const& elfPair : m_elfPairs)
            {
                if (IsSectionInRange(elfPair.first.first, elfPair.second) ||
                    IsSectionInRange(elfPair.first.second, elfPair.second) ||
                    IsSectionInRange(elfPair.second.first, elfPair.first) ||
                    IsSectionInRange(elfPair.second.second, elfPair.first))
                {
                    ++intersectingRangeCount;
                }
            }
            std::cout << intersectingRangeCount << std::endl;
        }

        virtual void CleanUp() override {}

    private:
        bool IsRangeFullyContained(SectionRange const& testRange, SectionRange const& otherRange) const
        {
            return testRange.first >= otherRange.first && testRange.second <= otherRange.second;
        }

        bool IsSectionInRange(int const testSection, SectionRange const& testRange)
        {
            return testSection >= testRange.first && testSection <= testRange.second;
        }
    };
}

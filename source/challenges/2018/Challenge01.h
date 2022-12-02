#pragma once

#include "../ChallengeAbstract.h"
#include <set>

namespace Year2018
{
    class Challenge01 : public ChallengeAbstract
    {
        std::vector<int> m_changes;

    public:
        virtual void SetUp(std::vector<std::string> const& inputLines) override
        {
            m_changes.resize(inputLines.size());
            for (size_t lineIndex = 0; lineIndex < inputLines.size(); ++lineIndex)
            {
                m_changes[lineIndex] = atoi(inputLines[lineIndex].c_str());
            }
        }

        virtual void Run_PartOne() override
        {
            int frequency = 0;
            for (int const change : m_changes)
            {
                frequency += change;
            }

            std::cout << frequency << std::endl;
        }

        virtual void Run_PartTwo() override
        {
            std::set<int> visitedFrequencies;
            int frequency = 0;
            int changeIndex = 0;

            while (visitedFrequencies.find(frequency) == visitedFrequencies.end())
            {
                visitedFrequencies.insert(frequency);
                frequency += m_changes[changeIndex++];
                changeIndex %= m_changes.size();
            }

            std::cout << frequency << std::endl;
        }

        virtual void CleanUp() override {}
    };
}

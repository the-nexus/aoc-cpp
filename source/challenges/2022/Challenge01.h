#pragma once

#include "../ChallengeAbstract.h"
#include <algorithm>

namespace Year2022
{
    class Challenge01 : public ChallengeAbstract
    {
    private:
        std::vector<int> m_elves;

    public:
        virtual void SetUp(std::vector<std::string> const& inputLines) override
        {
            m_elves.reserve(inputLines.size());
            m_elves.push_back(0);

            for (std::string const& inputLine : inputLines)
            {
                if (inputLine.size() > 0)
                {
                    m_elves.back() += atoi(inputLine.c_str());
                }
                else
                {
                    m_elves.push_back(0);
                }
            }

            std::sort(m_elves.rbegin(), m_elves.rend());
        }

        virtual void Run_PartOne() override
        {
            std::cout << m_elves[0] << std::endl;
        }

        virtual void Run_PartTwo() override
        {
            std::cout << (m_elves[0] + m_elves[1] + m_elves[2]) << std::endl;
        }

        virtual void CleanUp() override {}
    };
}

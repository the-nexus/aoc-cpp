#pragma once

#include "../ChallengeAbstract.h"
#include <algorithm>

namespace Year2022
{
    class Challenge01 final : public ChallengeAbstract
    {
    private:
        std::vector<int> m_elves;

    public:
        Challenge01(std::vector<std::string> const& inputLines)
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
    };
}

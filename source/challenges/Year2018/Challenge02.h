#pragma once

#include "../ChallengeAbstract.h"
#include <map>
#include <algorithm>

namespace Year2018
{
    class Challenge02 final : public ChallengeAbstract
    {
    private:
        std::vector<std::string> m_ids;

    public:
        Challenge02(std::vector<std::string> const& inputLines)
        {
            m_ids = inputLines;
            std::sort(m_ids.begin(), m_ids.end());
        }

        virtual void Run_PartOne() override
        {
            std::vector<std::string> idsCopy = m_ids;

            for (std::string& id : idsCopy)
            {
                std::sort(id.begin(), id.end());
            }

            int doublesCount = 0;
            int triplesCount = 0;

            for (std::string const& id : idsCopy)
            {
                bool hasDoubles = false;
                bool hasTriples = false;

                char currentChar = id[0];
                int currentCharCount = 1;

                for (size_t charIndex = 1; charIndex <= id.size(); ++charIndex)
                {
                    char nextChar = charIndex < id.size() ? id[charIndex] : ' ';
                    if (nextChar == currentChar)
                    {
                        ++currentCharCount;
                    }
                    else
                    {
                        if (currentCharCount == 2)
                        {
                            hasDoubles = true;
                            if (hasTriples)
                            {
                                break;
                            }
                        }
                        else if (currentCharCount == 3)
                        {
                            hasTriples = true;
                            if (hasDoubles)
                            {
                                break;
                            }
                        }

                        currentChar = nextChar;
                        currentCharCount = 1;
                    }
                }

                if (hasDoubles)
                {
                    ++doublesCount;
                }

                if (hasTriples)
                {
                    ++triplesCount;
                }
            }

            std::cout << (doublesCount * triplesCount) << std::endl;
        }

        virtual void Run_PartTwo() override
        {
            for (size_t firstIdIndex = 0; firstIdIndex < m_ids.size() - 1; ++firstIdIndex)
            {
                for (size_t secondIdIndex = firstIdIndex + 1; secondIdIndex < m_ids.size(); ++secondIdIndex)
                {
                    int failedMatchCount = 0;
                    for (size_t charIndex = 0; charIndex < m_ids[firstIdIndex].size(); ++charIndex)
                    {
                        if (m_ids[firstIdIndex][charIndex] != m_ids[secondIdIndex][charIndex] && ++failedMatchCount > 1)
                        {
                            break;
                        }
                    }

                    if (failedMatchCount == 1)
                    {
                        for (size_t charIndex = 0; charIndex < m_ids[firstIdIndex].size(); ++charIndex)
                        {
                            if (m_ids[firstIdIndex][charIndex] == m_ids[secondIdIndex][charIndex])
                            {
                                std::cout << m_ids[firstIdIndex][charIndex];
                            }
                        }

                        std::cout << std::endl;
                        return;
                    }
                }
            }
        }
    };
}


#pragma once

#include "Challenges/ChallengeAbstract.h"

namespace AOC::Challenges::Year2023
{
    class Challenge09 final : public ChallengeAbstract
    {
    private:
        std::vector<std::vector<int>> m_histories;

    public:
        Challenge09(std::vector<std::string> const& inputLines)
        {
            m_histories.reserve(inputLines.size());

            for (std::string const& line : inputLines)
            {
                std::vector<std::string> lineSplit;
                Tools::StringSplitter::SplitString(line, ' ', lineSplit);

                std::vector<int>& history = m_histories.emplace_back();
                history.reserve(lineSplit.size());

                for (std::string const& numberStr : lineSplit)
                {
                    history.push_back(atoi(numberStr.c_str()));
                }
            }
        }

        virtual void Run_PartOne() override
        {
            int extrapolationSum = 0;

            for (std::vector<int> const& history : m_histories)
            {
                extrapolationSum += ExtrapolateValue(history, true);
            }

            std::cout << extrapolationSum << std::endl;
        }

        virtual void Run_PartTwo() override
        {
            int extrapolationSum = 0;

            for (std::vector<int> const& history : m_histories)
            {
                extrapolationSum += ExtrapolateValue(history, false);
            }

            std::cout << extrapolationSum << std::endl;
        }

    private:
        static int ExtrapolateValue(std::vector<int> const& history, bool isBackExtrapolation)
        {
            std::vector<int> changes;
            changes.resize(history.size() - 1);

            bool isChangeZero = true;
            for (size_t i = 0; i < changes.size(); ++i)
            {
                changes[i] = history[i + 1] - history[i];
                isChangeZero &= changes[i] == 0;
            }

            int const extrapolatedValue = isChangeZero ? 0 : ExtrapolateValue(changes, isBackExtrapolation);
            return isBackExtrapolation ? history.back() + extrapolatedValue : history.front() - extrapolatedValue;
        }
    };
}

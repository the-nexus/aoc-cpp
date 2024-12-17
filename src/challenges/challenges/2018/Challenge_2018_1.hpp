
#pragma once

#include <set>
#include <string_view>

#include <core/manip/StringViewConverter.hpp>

#include "challenges/Challenge.hpp"

namespace aoc::challenges
{
    class Challenge_2018_1 final : public Challenge<2018, 1>
    {
        using Super = Challenge<2018, 1>;

    public:
        Challenge_2018_1(std::vector<std::string>&& inputLines)
            : Super(std::move(inputLines))
        {}

        void RunPartOne(std::ostream& outAnswer) override
        {
            int frequency = 0;

            for (std::string const& inputLine : GetInputLines())
            {
                frequency += GetFrequencyDelta(inputLine);
            }

            outAnswer << frequency;
        }

        void RunPartTwo(std::ostream& outAnswer) override
        {
            std::vector<std::string> const& inputLines = GetInputLines();
            size_t inputLineIndex = 0;

            std::set<int> frequencies;
            int frequency = 0;

            while (!frequencies.contains(frequency))
            {
                frequencies.insert(frequency);

                std::string const& inputLine = inputLines[inputLineIndex];
                inputLineIndex = (inputLineIndex + 1) % inputLines.size();

                frequency += GetFrequencyDelta(inputLine);
            }

            outAnswer << frequency;
        }

    private:
        int GetFrequencyDelta(std::string const& inputLine)
        {
                std::string_view inputView = { inputLine };
                inputView.remove_prefix(1);

                int const sign = inputLine[0] == '-' ? -1 : 1;
                int const value = core::StringViewConverter::ToInteger<int>(inputView);

                return value * sign;
        }
    };
}

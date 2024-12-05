
#pragma once

#include "challenges/Challenge.hpp"

namespace aoc::challenges
{
    class Challenge_2024_5 final : public Challenge<2024, 5>
    {
        using Super = Challenge<2024, 5>;

    public:
        Challenge_2024_5(std::vector<std::string>&& inputLines)
            : Super(std::move(inputLines)) 
        {}

        void RunPartOne(std::ostream& outAnswer) override
        {
            Super::RunPartOne(outAnswer);
        }

        void RunPartTwo(std::ostream& outAnswer) override
        {
            Super::RunPartTwo(outAnswer);
        }
    };
}


#pragma once

#include "challenges/Challenge.hpp"

namespace aoc::challenges
{
    class Challenge_2024_3 final : public Challenge<2024, 3>
    {
        using Super = Challenge<2024, 3>;

    public:
        Challenge_2024_3(std::vector<std::string>&& inputLines)
            : Super(std::move(inputLines))
        {}

        void RunPartOne(std::ostream& outAnswer) override;
        void RunPartTwo(std::ostream& outAnswer) override;
    };
}

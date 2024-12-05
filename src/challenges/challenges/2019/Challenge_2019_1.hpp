
#pragma once

#include "challenges/Challenge.hpp"

namespace aoc::challenges
{
    class Challenge_2019_1 final : public Challenge<2019, 1>
    {
        using Super = Challenge<2019, 1>;

    public:
        Challenge_2019_1(std::vector<std::string>&& inputLines)
            : Super(std::move(inputLines)) 
        {}

        void RunPartOne(std::ostream& outAnswer) override
        {
            unsigned int totalFuel = 0;
            for (std::string const& inputLine : GetInputLines())
            {
                int weight = std::stoi(inputLine);
                totalFuel += static_cast<unsigned int>(GetRequiredFuel(weight));
            }

            outAnswer << totalFuel;
        }

        void RunPartTwo(std::ostream& outAnswer) override
        {
            unsigned int totalFuel = 0;
            for (std::string const& inputLine : GetInputLines())
            {
                int weight = std::stoi(inputLine);
                while (weight > 0)
                {
                    weight = GetRequiredFuel(weight);
                    if (weight > 0)
                    {
                        totalFuel += weight;
                    }
                }
            }

            outAnswer << totalFuel;
        }

    private:
        static int GetRequiredFuel(int const weight) { return (weight / 3) - 2; }
    };
}

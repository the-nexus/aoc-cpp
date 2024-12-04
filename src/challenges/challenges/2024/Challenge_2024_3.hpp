
#pragma once

#include "challenges/Challenge.hpp"

#include <regex>

namespace aoc::challenges
{
    class Challenge_2024_3 final : public Challenge<2024, 3>
    {
        using Super = Challenge<2024, 3>;

    public:
        Challenge_2024_3(std::vector<std::string>&& inputLines)
            : Super(std::move(inputLines)) 
        {}

        void RunPartOne(std::ostream& outAnswer) override
        {
            std::regex pattern("mul\\(([0-9]+),([0-9]+)\\)");

            int sumOfMultiplications = 0;

            for (std::string const& line : GetInputLines())
            {
                std::string remainingLine = line;
                for (std::smatch result; std::regex_search(remainingLine, result, pattern); )
                {
                    int const firstParam = std::stoi(result[1].str());
                    int const secondParam = std::stoi(result[2].str());
                    sumOfMultiplications += firstParam * secondParam;

                    remainingLine = result.suffix();
                }
            }

            outAnswer << sumOfMultiplications;
        }

        void RunPartTwo(std::ostream& outAnswer) override 
        {
            std::regex pattern("(mul\\(([0-9]+),([0-9]+)\\))|(do\\(\\))|(don't\\(\\))");

            bool areMultiplicationEnabled = true;
            int sumOfMultiplications = 0;

            for (std::string const& line : GetInputLines())
            {
                std::string remainingLine = line;
                for (std::smatch result; std::regex_search(remainingLine, result, pattern); )
                {
                    if (result[5].length() > 0)
                    {
                        areMultiplicationEnabled = false;
                    }
                    else if (result[4].length() > 0)
                    {
                        areMultiplicationEnabled = true;
                    }
                    else if (areMultiplicationEnabled)
                    {
                        int const firstParam = std::stoi(result[2].str());
                        int const secondParam = std::stoi(result[3].str());
                        sumOfMultiplications += firstParam * secondParam;
                    }

                    remainingLine = result.suffix();
                }
            }

            outAnswer << sumOfMultiplications;
        }
    };
}

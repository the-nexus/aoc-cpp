
#pragma once

#include <Tools/Utilities/Challenge.hpp>
#include <iostream>

namespace AOC::Challenges
{
    class Challenge_2020_12 final : public Tools::Challenge<2020, 12>
    {
    public:
        Challenge_2020_12(std::vector<std::string>&& inputLines) : Tools::Challenge<2020, 12>(std::move(inputLines)) {}

        void RunPartOne() override { std::cout << "Challenge_2020_12::RunPartOne()" << std::endl; }
        void RunPartTwo() override { std::cout << "Challenge_2020_12::RunPartTwo()" << std::endl; }
    };
}

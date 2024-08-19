
#pragma once

#include <Tools/Utilities/Challenge.hpp>
#include <iostream>

namespace AOC::Challenges
{
    class Challenge_2020_13 final : public Tools::Challenge<2020, 13>
    {
    public:
        Challenge_2020_13(std::vector<std::string>&& inputLines) : Tools::Challenge<2020, 13>(std::move(inputLines)) {}

        void RunPartOne() override { std::cout << "Challenge_2020_13::RunPartOne()" << std::endl; }
        void RunPartTwo() override { std::cout << "Challenge_2020_13::RunPartTwo()" << std::endl; }
    };
}

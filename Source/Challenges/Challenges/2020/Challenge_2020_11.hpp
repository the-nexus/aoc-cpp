
#pragma once

#include <Tools/Utilities/Challenge.hpp>
#include <iostream>

namespace AOC::Challenges
{
    class Challenge_2020_11 final : public Tools::Challenge<2020, 11>
    {
    public:
        Challenge_2020_11(std::vector<std::string>&& inputLines) : Tools::Challenge<2020, 11>(std::move(inputLines)) {}

        void RunPartOne() override { std::cout << "Challenge_2020_11::RunPartOne()" << std::endl; }
        void RunPartTwo() override { std::cout << "Challenge_2020_11::RunPartTwo()" << std::endl; }
    };
}

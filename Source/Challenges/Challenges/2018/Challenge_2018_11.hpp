
#pragma once

#include <Tools/Utilities/Challenge.hpp>

namespace AOC::Challenges
{
    class Challenge_2018_11 final : public Tools::Challenge<2018, 11>
    {
    public:
        Challenge_2018_11(std::vector<std::string>&& inputLines)
            : Tools::Challenge<2018, 11>(std::move(inputLines)) 
        {}

        // ========================================================================================

        void RunPartOne(std::ostream& outAnswer) override
        {
            Tools::Challenge<2018, 11>::RunPartOne(outAnswer);
        }

        // ========================================================================================

        void RunPartTwo(std::ostream& outAnswer) override 
        {
            Tools::Challenge<2018, 11>::RunPartTwo(outAnswer);
        }
    };
}

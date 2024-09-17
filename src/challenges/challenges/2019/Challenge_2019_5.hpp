
#pragma once

#include "challenges/Challenge.hpp"
#include "challenges/2019/intcode/Computer.hpp"

namespace aoc::challenges
{
    class Challenge_2019_5 final : public Challenge<2019, 5>
    {
        using Super = Challenge<2019, 5>;

    public:
        Challenge_2019_5(std::vector<std::string>&& inputLines)
            : Super(std::move(inputLines)) 
        {}

        void RunPartOne(std::ostream& outAnswer) override
        {
            intcode2019::Computer computer { GetInputLine(0) };
            computer.PushInputData(1);

            while (!computer.HasHalted())
            {
                computer.Step();
            }

            int diagnosticCode = 0;
            while (std::optional<int> const outputData = computer.PopOutputData())
            {
                diagnosticCode = outputData.value();
            }

            outAnswer << diagnosticCode;
        }

        void RunPartTwo(std::ostream& outAnswer) override 
        {
            Super::RunPartTwo(outAnswer);
        }
    };
}


#pragma once

#include "challenges/Challenge.hpp"
#include "challenges/2019/intcode/IntcodeProgram.hpp"

namespace aoc::challenges
{
    class Challenge_2019_2 final : public Challenge<2019, 2>
    {
        using Super = Challenge<2019, 2>;

    public:
        Challenge_2019_2(std::vector<std::string>&& inputLines)
            : Super(std::move(inputLines)) 
        {}

        void RunPartOne(std::ostream& outAnswer) override
        {
            IntcodeProgram program { GetInputLines()[0] };
            program.SetAt(1, 12);
            program.SetAt(2, 2);

            while (program.Step()) {}

            outAnswer << program.GetAt(0);
        }

        void RunPartTwo(std::ostream& outAnswer) override 
        {
            IntcodeProgram program { GetInputLines()[0] };
            for (intcode_t noun = 0; noun <= 99; ++noun)
            {
                for (intcode_t verb = 0; verb <= 99; ++verb)
                {
                    program.Reset();
                    program.SetAt(1, noun);
                    program.SetAt(2, verb);

                    while (program.Step()) {}

                    if (program.GetAt(0) == 19690720)
                    {
                        outAnswer << (noun * 100 + verb);
                        return;
                    }
                }
            }

        }
    };
}


#pragma once

#include "challenges/Challenge.hpp"
#include "challenges/2019/intcode/Computer.hpp"

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
            intcode2019::Computer computer = { GetInputLine(0) };
            computer.WriteData(1, 12);
            computer.WriteData(2, 2);

            while (!computer.HasHalted())
            {
                computer.Step();
            }

            int result;
            computer.ReadData(0, result);
            outAnswer << result;
        }

        void RunPartTwo(std::ostream& outAnswer) override
        {
            intcode2019::Computer computer = { GetInputLine(0) };
            for (int noun = 0; noun <= 99; ++noun)
            {
                for (int verb = 0; verb <= 99; ++verb)
                {
                    computer.Reset();
                    computer.WriteData(1, noun);
                    computer.WriteData(2, verb);

                    while (!computer.HasHalted())
                    {
                        computer.Step();
                    }

                    int result;
                    computer.ReadData(0, result);

                    if (result == 19690720)
                    {
                        outAnswer << (noun * 100 + verb);
                        return;
                    }
                }
            }
        }
    };
}

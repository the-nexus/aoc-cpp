
#pragma once

#include "challenges/Challenge.hpp"
#include "challenges/2019/intcode/Computer.hpp"
#include "challenges/2019/intcode/io/IOQueue.hpp"

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
            intcode2019::Computer computer = { intcode2019::Computer::CompileProgram(GetInputLine(0)) };

            intcode2019::IOQueue dataIn, dataOut;
            computer.SetInputPipe(&dataIn);
            computer.SetOutputPipe(&dataOut);

            dataIn.WriteData(1);

            while (!computer.HasHalted())
            {
                computer.Step();
            }

            int diagnosticCode = 0;
            while (dataOut.ReadData(diagnosticCode)) {}

            outAnswer << diagnosticCode;
        }

        void RunPartTwo(std::ostream& outAnswer) override 
        {
            intcode2019::Computer computer = { intcode2019::Computer::CompileProgram(GetInputLine(0)) };

            intcode2019::IOQueue dataIn, dataOut;
            computer.SetInputPipe(&dataIn);
            computer.SetOutputPipe(&dataOut);

            dataIn.WriteData(5);

            while (!computer.HasHalted())
            {
                computer.Step();
            }

            int diagnosticCode = 0;
            while (dataOut.ReadData(diagnosticCode)) {}

            outAnswer << diagnosticCode;
        }
    };
}

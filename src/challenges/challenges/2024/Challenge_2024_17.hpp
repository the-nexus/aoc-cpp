
#pragma once

#include "challenges/Challenge.hpp"

#include <cmath>

namespace aoc::challenges
{
    class Challenge_2024_17 final : public Challenge<2024, 17>
    {
        using Super = Challenge<2024, 17>;

        enum class Opcode : int
        {
            ADV = 0,
            BXL,
            BST,
            JNZ,
            BXC,
            OUT,
            BDV,
            CDV
        };

        struct ComputerState
        {
            std::vector<int> _program;
            std::vector<int> _output;
            size_t _programCounter = 0;
            int _registerA = 0;
            int _registerB = 0;
            int _registerC = 0;
        };

    public:
        Challenge_2024_17(std::vector<std::string>&& inputLines)
            : Super(std::move(inputLines))
        {}

        void RunPartOne(std::ostream& outAnswer) override
        {
            ComputerState computerState;
            InitializeComputer(computerState);

            while (computerState._programCounter < computerState._program.size())
            {
                StepComputer(computerState);
            }

            outAnswer << computerState._output[0];
            for (size_t outputIndex = 1u; outputIndex < computerState._output.size(); ++outputIndex)
            {
                outAnswer << ',' << computerState._output[outputIndex];
            }
        }

        void RunPartTwo(std::ostream& outAnswer) override
        {
            Super::RunPartTwo(outAnswer);
        }

        void InitializeComputer(ComputerState& outComputerState) const
        {
            ReadRegisterInputValue(0u, outComputerState._registerA);
            ReadRegisterInputValue(1u, outComputerState._registerB);
            ReadRegisterInputValue(2u, outComputerState._registerC);

            std::string const& programLine = GetInputLine(4u);
            outComputerState._program.reserve((programLine.size() - 9u) / 2u + 1u);
            for (size_t tokenIndex = 9u; tokenIndex < programLine.size(); tokenIndex += 2u)
            {
                outComputerState._program.push_back(static_cast<int>(programLine[tokenIndex] - '0'));
            }
        }

        void ReadRegisterInputValue(size_t const lineIndex, int& outValue) const
        {
            std::string const& line = GetInputLine(lineIndex);
            outValue = 0;

            for (size_t tokenIndex = 12u; tokenIndex < line.size(); ++tokenIndex)
            {
                outValue = outValue * 10 + static_cast<int>(line[tokenIndex] - '0');
            }
        }

        static void StepComputer(ComputerState& computerState)
        {
            Opcode const opcode = static_cast<Opcode>(computerState._program[computerState._programCounter++]);
            int const operand = computerState._program[computerState._programCounter++];

            switch (opcode)
            {
                case Opcode::ADV: 
                computerState._registerA = computerState._registerA >> GetComboValue(computerState, operand);
                break;

                case Opcode::BXL:
                computerState._registerB = computerState._registerB ^ operand;
                break;

                case Opcode::BST:
                computerState._registerB = GetComboValue(computerState, operand) & 0b0111;
                break;

                case Opcode::JNZ:
                if (computerState._registerA != 0)
                {
                    computerState._programCounter = operand;
                }
                break;

                case Opcode::BXC:
                computerState._registerB = computerState._registerB ^ computerState._registerC;
                break;

                case Opcode::OUT:
                computerState._output.push_back(GetComboValue(computerState, operand) & 0b0111);
                break;

                case Opcode::BDV:
                computerState._registerB = computerState._registerA >> GetComboValue(computerState, operand);
                break;

                case Opcode::CDV:
                computerState._registerC = computerState._registerA >> GetComboValue(computerState, operand);
                break;
            }
        }

        static int GetComboValue(ComputerState const& computerState, int const operand)
        {
            if (operand == 4)
            {
                return computerState._registerA;
            }

            if (operand == 5)
            {
                return computerState._registerB;
            }

            if (operand == 6)
            {
                return computerState._registerC;
            }

            if (operand == 7)
            {
                throw 7;
            }

            return operand;
        }
    };
}

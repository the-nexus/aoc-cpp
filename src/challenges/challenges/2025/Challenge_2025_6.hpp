
#pragma once

#include <core/manip/StringSplitter.hpp>

#include "challenges/Challenge.hpp"

namespace aoc::challenges
{
    class Challenge_2025_6 final : public Challenge<2025, 6>
    {
        using Super = Challenge<2025, 6>;

        enum class OperationType
        {
            Add,
            Multiply
        };

        struct MathProblem
        {
            OperationType _operation = OperationType::Add;
            std::vector<unsigned long long> _operands;
            size_t _textWidth = 1;
        };

    public:
        Challenge_2025_6(std::vector<std::string>&& inputLines)
            : Super(std::move(inputLines))
        {}

        void RunPartOne(std::ostream& outAnswer) override
        {
            std::vector<MathProblem> mathProblems;
            InitializeOperations(mathProblems);
            InitializeOperandsHorizontal(mathProblems);

            unsigned long long resultSum = 0;
            for (const MathProblem& mathProblem : mathProblems)
            {
                resultSum += ResolveMathProblem(mathProblem);
            }

            outAnswer << resultSum;
        }

        void RunPartTwo(std::ostream& outAnswer) override
        {
            std::vector<MathProblem> mathProblems;
            InitializeOperations(mathProblems);
            InitializeOperandsVertical(mathProblems);

            unsigned long long resultSum = 0;
            for (const MathProblem& mathProblem : mathProblems)
            {
                resultSum += ResolveMathProblem(mathProblem);
            }

            outAnswer << resultSum;
        }

        void InitializeOperations(std::vector<MathProblem>& outMathProblems) const
        {
            const std::string& operationLine = GetInputLines().back();
            outMathProblems.reserve(operationLine.size());

            for (const char token : operationLine)
            {
                if (token == ' ')
                {
                    ++outMathProblems.back()._textWidth;
                }
                else
                {
                    if (!outMathProblems.empty())
                    {
                        --outMathProblems.back()._textWidth;
                    }

                    if (token == '+')
                    {
                        MathProblem& newProblem = outMathProblems.emplace_back();
                        newProblem._operation = OperationType::Add;
                    }
                    else if (token == '*')
                    {
                        MathProblem& newProblem = outMathProblems.emplace_back();
                        newProblem._operation = OperationType::Multiply;
                    }
                }
            }
        }

        void InitializeOperandsHorizontal(std::vector<MathProblem>& mathProblems) const
        {
            const std::vector<std::string>& lines = GetInputLines();
            const size_t operandCount = lines.size() - 1;

            size_t tokenOffset = 0;
            for (MathProblem& mathProblem : mathProblems)
            {
                const size_t tokenCount = mathProblem._textWidth;
                mathProblem._operands.resize(operandCount, 0);

                for (size_t operandIndex = 0; operandIndex < operandCount; ++operandIndex)
                {
                    for (size_t tokenIndex = 0; tokenIndex < tokenCount; ++tokenIndex)
                    {
                        const char token = lines[operandIndex][tokenOffset + tokenIndex];
                        if (token < '0' || token > '9')
                        {
                            continue;
                        }

                        mathProblem._operands[operandIndex] *= 10;
                        mathProblem._operands[operandIndex] += static_cast<unsigned long long>(token - '0');
                    }
                }

                tokenOffset += mathProblem._textWidth + 1;
            }
        }

        void InitializeOperandsVertical(std::vector<MathProblem>& mathProblems) const
        {
            const std::vector<std::string>& lines = GetInputLines();
            const size_t tokenCount = lines.size() - 1;

            size_t operandOffset = 0;
            for (MathProblem& mathProblem : mathProblems)
            {
                const size_t operandCount = mathProblem._textWidth;
                mathProblem._operands.resize(operandCount, 0);

                for (size_t operandIndex = 0; operandIndex < operandCount; ++operandIndex)
                {
                    for (size_t tokenIndex = 0; tokenIndex < tokenCount; ++tokenIndex)
                    {
                        const char token = lines[tokenIndex][operandOffset + operandIndex];
                        if (token < '0' || token > '9')
                        {
                            continue;
                        }

                        mathProblem._operands[operandIndex] *= 10;
                        mathProblem._operands[operandIndex] += static_cast<unsigned long long>(token - '0');
                    }
                }

                operandOffset += mathProblem._textWidth + 1;
            }
        }

        unsigned long long ResolveMathProblem(const MathProblem& mathProblem) const
        {
            if (mathProblem._operation == OperationType::Add)
            {
                unsigned result = 0;
                for (unsigned long long operand : mathProblem._operands)
                {
                    result += operand;
                }

                return result;
            }
            else if (mathProblem._operation == OperationType::Multiply)
            {
                unsigned long long result = 1;
                for (unsigned long long operand : mathProblem._operands)
                {
                    result *= operand;
                }

                return result;
            }
            else
            {
                return 0;
            }
        }
    };
}

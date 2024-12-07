
#pragma once

#include "challenges/Challenge.hpp"

namespace aoc::challenges
{
    class Challenge_2024_7 final : public Challenge<2024, 7>
    {
        using Super = Challenge<2024, 7>;

        struct Equation
        {
            unsigned long long m_result = 0;
            std::vector<unsigned long long> m_operands;
        };

    public:
        Challenge_2024_7(std::vector<std::string>&& inputLines)
            : Super(std::move(inputLines))
        {}

        void RunPartOne(std::ostream& outAnswer) override
        {
            std::vector<Equation> equations;
            AssembleEquations(equations);

            unsigned long long resultSum = 0;
            unsigned long long allResultSum = 0;
            size_t validCount = 0;
            for (Equation const& equation : equations)
            {
                if (IsValidEquation(equation))
                {
                    resultSum += equation.m_result;
                    ++validCount;
                }
                allResultSum += equation.m_result;
            }

            outAnswer << resultSum << " (" << validCount << ") / (" << equations.size() << ") " << allResultSum;
        }

        void RunPartTwo(std::ostream& outAnswer) override
        {
            Super::RunPartTwo(outAnswer);
        }

        void AssembleEquations(std::vector<Equation>& outEquations) const
        {
            outEquations.reserve(GetInputLines().size());
            for (std::string const& line : GetInputLines())
            {
                size_t const separatorCount = std::count(std::cbegin(line), std::cend(line), ' ');

                Equation& newEquation = outEquations.emplace_back();
                newEquation.m_operands.reserve(separatorCount);

                auto tokenIt = std::cbegin(line);
                auto const endIt = std::cend(line);

                for (; tokenIt != endIt; ++tokenIt)
                {
                    if (*tokenIt == ':')
                    {
                        ++tokenIt;
                        break;
                    }

                    newEquation.m_result = newEquation.m_result * 10 + static_cast<unsigned long long>(*tokenIt - '0');
                }

                for (; tokenIt != endIt; ++tokenIt)
                {
                    if (*tokenIt == ' ')
                    {
                        newEquation.m_operands.push_back(0);
                        continue;
                    }

                    unsigned long long& operand = newEquation.m_operands.back();
                    operand = operand * 10 + static_cast<unsigned long long>(*tokenIt - '0');
                }
            }
        }

        static bool IsValidEquation(Equation const& equation, size_t const operandIndex = 0, unsigned long long const currentResult = 0)
        {
            if (operandIndex == equation.m_operands.size())
            {
                return currentResult == equation.m_result;
            }

            if (currentResult >= equation.m_result)
            {
                return false;
            }

            size_t const nextOperandIndex = operandIndex + 1;
            unsigned long long const testOperand = equation.m_operands[operandIndex];

            if (IsValidEquation(equation, nextOperandIndex, currentResult * testOperand))
            {
                return true;
            }

            if (IsValidEquation(equation, nextOperandIndex, currentResult + testOperand))
            {
                return true;
            }

            return false;
        }
    };
}

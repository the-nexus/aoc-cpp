
// This challenge implementation uses a .cpp file only because the
// include of <regex> adds a significant amount of compile time

#include "Challenge_2024_3.hpp"

#include <regex>

using namespace aoc::challenges;

void Challenge_2024_3::RunPartOne(std::ostream& outAnswer)
{
    std::regex pattern("mul\\(([0-9]+),([0-9]+)\\)");

    int sumOfMultiplications = 0;

    for (std::string const& line : GetInputLines())
    {
        std::string remainingLine = line;
        for (std::smatch result; std::regex_search(remainingLine, result, pattern); )
        {
            int const firstParam = std::stoi(result[1].str());
            int const secondParam = std::stoi(result[2].str());
            sumOfMultiplications += firstParam * secondParam;

            remainingLine = result.suffix();
        }
    }

    outAnswer << sumOfMultiplications;
}

void Challenge_2024_3::RunPartTwo(std::ostream& outAnswer)
{
    std::regex pattern("(mul\\(([0-9]+),([0-9]+)\\))|(do\\(\\))|(don't\\(\\))");

    bool areMultiplicationEnabled = true;
    int sumOfMultiplications = 0;

    for (std::string const& line : GetInputLines())
    {
        std::string remainingLine = line;
        for (std::smatch result; std::regex_search(remainingLine, result, pattern); )
        {
            if (result[5].length() > 0)
            {
                areMultiplicationEnabled = false;
            }
            else if (result[4].length() > 0)
            {
                areMultiplicationEnabled = true;
            }
            else if (areMultiplicationEnabled)
            {
                int const firstParam = std::stoi(result[2].str());
                int const secondParam = std::stoi(result[3].str());
                sumOfMultiplications += firstParam * secondParam;
            }

            remainingLine = result.suffix();
        }
    }

    outAnswer << sumOfMultiplications;
}

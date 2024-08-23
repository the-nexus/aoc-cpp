
#include <iostream>
#include <sstream>

#include <challenges/Factory.hpp>
#include <core/io/FileReader.hpp>

int main(int argc, char* argv[])
{
    int const year = 2018;
    int const day = 1;
    bool const shouldRunPartOne = true;
    bool const shouldRunPartTwo = true;

    std::string filePath = "";

    std::vector<std::string> inputLines;
    if (!aoc::core::FileReader::GetLines(filePath, inputLines))
    {
        std::cerr << "Could not read input file for [year=" << year << ", day=" << day << "]" << std::endl;
        return -1;
    }

    aoc::challenges::Factory::RegisterAll();
    auto challenge = aoc::challenges::Factory::Produce({year, day}, std::move(inputLines));
    if (!challenge)
    {
        std::cerr << "Could not find challenge for [year=" << year << ", day=" << day << "]" << std::endl;
        return -1;
    }

    if (shouldRunPartOne)
    {
        challenge->RunPartOne(std::cout);
        std::cout << std::endl;
    }

    if (shouldRunPartTwo)
    {
        challenge->RunPartTwo(std::cout);
        std::cout << std::endl;
    }
}
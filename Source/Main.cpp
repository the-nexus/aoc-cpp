
#include <iostream>
#include <sstream>

#include <Challenges/Factory.hpp>
#include <Tools/FileReader.h>

int main(int argc, char* argv[])
{
    int const year = 2018;
    int const day = 1;
    bool const shouldRunPartOne = true;
    bool const shouldRunPartTwo = true;

    std::string filePath = "";

    std::vector<std::string> inputLines;
    if (!AOC::Tools::FileReader::GetLines(filePath, inputLines))
    {
        std::cerr << "Could not read input file for [year=" << year << ", day=" << day << "]" << std::endl;
        return -1;
    }

    AOC::Challenges::Factory::RegisterAll();
    auto challenge = AOC::Challenges::Factory::Produce({year, day}, std::move(inputLines));
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
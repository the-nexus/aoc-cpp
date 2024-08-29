
#include <format>
#include <iostream>

#include <challenges/Factory.hpp>
#include <core/io/FileReader.hpp>

std::filesystem::path GetInputFilePath(std::filesystem::path const& exePath, int const year, int const day)
{
    std::filesystem::path filePath = exePath;
    std::string directoryName = "";
    do
    {
        directoryName = filePath.filename();
        filePath = filePath.parent_path();
    }
    while (directoryName.size() > 0 && directoryName != "build");

    if (directoryName.size() > 0)
    {
        return filePath / "res" / "input" / std::format("{}", year) / std::format("Input_{}_{}.txt", year, day);
    }

    return std::filesystem::path {};
}

int main(int argc, char* argv[])
{
    int const year = 2018;
    int const day = 1;
    bool const shouldRunPartOne = true;
    bool const shouldRunPartTwo = true;

    std::filesystem::path inputFilePath = GetInputFilePath(argv[0], year, day);
    if (!std::filesystem::exists(inputFilePath))
    {
        std::cerr << std::format("Could not find input file [path={}]", inputFilePath.string()) << std::endl;
        return -1;
    }

    std::vector<std::string> inputLines;
    if (!aoc::core::FileReader::GetLines(inputFilePath, inputLines))
    {
        std::cerr << std::format("Could not read input file [path={}]", year, day) << std::endl;
        return -1;
    }

    aoc::challenges::Factory::RegisterAll();
    auto challenge = aoc::challenges::Factory::Produce({year, day}, std::move(inputLines));
    if (!challenge)
    {
        std::cerr << std::format("Could not find challenge implementation [year={}, day={}]", year, day) << std::endl;
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
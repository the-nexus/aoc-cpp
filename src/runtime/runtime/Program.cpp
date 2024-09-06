
#include "Program.hpp"

#include <format>
#include <iostream>

#include <challenges/Factory.hpp>
#include <core/io/FileReader.hpp>

using namespace aoc::runtime;

int Program::Launch(std::vector<std::string_view> const& args)
{
    ParseArguments(args);
    FixArguments();

    if (!std::filesystem::exists(m_inputFilePath.value()))
    {
        std::cerr << std::format("Could not find input file [path={}]", m_inputFilePath->string()) << std::endl;
        return -1;
    }

    std::vector<std::string> inputLines;
    if (!aoc::core::FileReader::GetLines(m_inputFilePath.value(), inputLines))
    {
        std::cerr << std::format("Could not read input file [path={}]", m_year.value(), m_day.value()) << std::endl;
        return -1;
    }

    aoc::challenges::Factory::RegisterAll();
    auto challenge = aoc::challenges::Factory::Produce({m_year.value(), m_day.value()}, std::move(inputLines));
    if (!challenge)
    {
        std::cerr << std::format("Could not find challenge implementation [year={}, day={}]", m_year.value(), m_day.value()) << std::endl;
        return -1;
    }

    if (m_shouldRunPartOne.value())
    {
        challenge->RunPartOne(std::cout);
        std::cout << std::endl;
    }

    if (m_shouldRunPartTwo.value())
    {
        challenge->RunPartTwo(std::cout);
        std::cout << std::endl;
    }

    return 0;
}

void Program::FixArguments()
{
    if (!m_year)
    {
        int year;
        std::cout << "Year: ";
        std::cin >> year;
        m_year = std::make_optional(year);
    }

    if (!m_day)
    {
        int day;
        std::cout << "Day: ";
        std::cin >> day;
        m_day = std::make_optional(day);
    }

    if (!m_shouldRunPartOne && !m_shouldRunPartTwo)
    {
        m_shouldRunPartOne = std::make_optional(true);
        m_shouldRunPartTwo = std::make_optional(true);
    }
    else if (m_shouldRunPartOne)
    {
        m_shouldRunPartTwo = std::make_optional(false);
    }
    else if (m_shouldRunPartTwo)
    {
        m_shouldRunPartOne = std::make_optional(false);
    }

    if (!m_inputFilePath)
    {
        m_inputFilePath = std::make_optional(GetInputFilePath(m_year.value(), m_day.value()));
    }
}

void Program::ParseArguments(std::vector<std::string_view> const& args)
{
    m_exePath = std::filesystem::path(args[0]);

    for (size_t index = 1; index < args.size(); ++index)
    {
        std::string_view arg = args[index];
        if (arg.size() <= 1)
        {
            continue;
        }

        if (arg[0] != '-')
        {
            continue;
        }

        if (arg.compare("-i") == 0)
        {
            if (index + 1 < args.size())
            {
                std::filesystem::path const path = std::filesystem::path(args[index + 1]);
                m_inputFilePath = std::make_optional(path);
                ++index;
            }
        }
        else if (arg.compare("-y") == 0)
        {
            if (index + 1 < args.size())
            {
                int const value = core::StringViewConverter::ToInteger<int>(args[index + 1]);
                m_year = std::make_optional(value);
                ++index;
            }
        }
        else if (arg.compare("-d") == 0)
        {
            if (index + 1 < args.size())
            {
                int const value = core::StringViewConverter::ToInteger<int>(args[index + 1]);
                m_day = std::make_optional(value);
                ++index;
            }
        }
        else if (arg.compare("-p1") == 0)
        {
            m_shouldRunPartOne = std::make_optional(true);
        }
        else if (arg.compare("-p2") == 0)
        {
            m_shouldRunPartTwo = std::make_optional(true);
        }
        else if (arg.compare("-t") == 0)
        {
            // TODO: Run timer
        }
        else if (arg.compare("-h") == 0)
        {
            PrintArgumentsHelp();
        }
    }
}

void Program::PrintArgumentsHelp() const
{
    std::cout << "AdventOfCode [-h] [-i] PATH [-y] YEAR [-d] DAY [-p1] [-p2] [-t]\n"
        "[-i ]  PATH  Path to a specific input file to use with the challenge program.\n"
        "[-y ]  YEAR  Year of the challenge program to execute.\n"
        "[-d ]  DAY   Day of the challenge program to execute.\n"
        "[-p1]        If specified without --part2 being specified, will only run the first part of the challenge program.\n"
        "[-p2]        If specified without --part1 being specified, will only run the second part of the challenge program.\n"
        "[-t ]        Will measure the execution time of the program, excluding argument parsing.\n"
        "[-h ]        Prints this message.\n";
}

std::filesystem::path Program::GetInputFilePath(int const year, int const day) const
{
    std::filesystem::path filePath = m_exePath;
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
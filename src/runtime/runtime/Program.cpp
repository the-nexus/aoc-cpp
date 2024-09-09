
#include "Program.hpp"

#include <format>
#include <iostream>

#include <challenges/Factory.hpp>
#include <core/io/FileReader.hpp>
#include <core/time/ChronoTimer.hpp>

using namespace aoc::runtime;

int Program::Launch(std::vector<std::string_view> const& args)
{
    core::ChronoTimer configTimer, programTimer, totalTimer;
    totalTimer.Start();
    configTimer.Start();

    std::optional<Config> const config = MakeConfig(args);
    if (!config)
    {
        DisplayHelp();
        return 0;
    }

    if (!std::filesystem::exists(config->m_inputFilePath))
    {
        std::cerr << std::format("Could not find input file [path={}]", config->m_inputFilePath.string()) << std::endl;
        return 1;
    }

    std::vector<std::string> inputLines;
    if (!core::FileReader::GetLines(config->m_inputFilePath, inputLines))
    {
        std::cerr << std::format("Could not read input file [path={}]",config->m_year, config->m_day) << std::endl;
        return 1;
    }

    configTimer.Stop();
    programTimer.Start();

    challenges::Factory::RegisterAll();
    auto challenge = challenges::Factory::Produce({config->m_year, config->m_day}, std::move(inputLines));
    if (!challenge)
    {
        std::cerr << std::format("Could not find challenge implementation [year={}, day={}]", config->m_year, config->m_day) << std::endl;
        return 1;
    }

    if (config->m_runPartOne)
    {
        challenge->RunPartOne(std::cout);
        std::cout << std::endl;
    }

    if (config->m_runPartTwo)
    {
        challenge->RunPartTwo(std::cout);
        std::cout << std::endl;
    }

    programTimer.Stop();
    totalTimer.Stop();

    if (config->m_displayExecutionTime)
    {
        std::cout << std::format(
            "\nConfig  {} seconds"
            "\nProgram {} seconds"
            "\nTotal   {} seconds", 
            configTimer.GetElapsedTime(),
            programTimer.GetElapsedTime(),
            totalTimer.GetElapsedTime())
            << std::endl;
    }

    return 0;
}

std::optional<Program::Config> Program::MakeConfig(std::vector<std::string_view> const& args)
{
    std::optional<std::filesystem::path> inputFilePath = std::nullopt;
    std::optional<int> year = std::nullopt;
    std::optional<int> day = std::nullopt;
    bool hasPartOneFlag = false;
    bool hasPartTwoFlag = false;
    bool hasTimerFlag = false;

    for (size_t argIndex = 1; argIndex < args.size(); ++argIndex)
    {
        std::string_view const& arg = args[argIndex];
        if (arg[0] != '-')
        {
            // We don't have any mandatory arg, everything should start by '-'
            return std::nullopt;
        }

        // Check for flag arguments
        if (arg.compare("-p1") == 0)
        {
            hasPartOneFlag = true;
            continue;
        }

        if (arg.compare("-p2") == 0)
        {
            hasPartTwoFlag = true;
            continue;
        }

        if (arg.compare("-t") == 0)
        {
            hasTimerFlag = true;
            continue;
        }

        if (arg.compare("-h") == 0)
        {
            return std::nullopt;
        }

        // Check for param arguments
        size_t paramIndex = argIndex + 1;
        if (paramIndex >= args.size())
        {
            // Missing param value, not enough arguments specified
            return std::nullopt;
        }

        std::string_view const& param = args[paramIndex];
        if (param[0] == '-')
        {
            // Missing param value before next argument
            return std::nullopt;
        }

        if (arg.compare("-i") == 0)
        {
            std::filesystem::path const path = { param };
            inputFilePath = std::make_optional(path);
            ++argIndex;
            continue;
        }

        if (arg.compare("-y") == 0)
        {
            year = std::make_optional(core::StringViewConverter::ToInteger<int>(param));
            ++argIndex;
            continue;
        }

        if (arg.compare("-d") == 0)
        {
            day = std::make_optional(core::StringViewConverter::ToInteger<int>(param));
            ++argIndex;
            continue;
        }
    }

    Config config;
    config.m_year = year.has_value() ? year.value() : QueryYear();
    config.m_day = day.has_value() ? day.value() : QueryDay();
    config.m_runPartOne = hasPartOneFlag || !hasPartTwoFlag;
    config.m_runPartTwo = hasPartTwoFlag || !hasPartOneFlag;
    config.m_inputFilePath = inputFilePath.has_value() ? inputFilePath.value() : GetInputFilePath({ args[0] }, config.m_year, config.m_day);
    config.m_displayExecutionTime = hasTimerFlag;

    return std::make_optional(config);
}

std::filesystem::path Program::GetInputFilePath(std::filesystem::path const& executionPath, int const year, int const day)
{
    std::filesystem::path filePath = executionPath;
    std::string directoryName = "";
    do
    {
        directoryName = filePath.filename().string();
        filePath = filePath.parent_path();
    }
    while (directoryName.size() > 0 && directoryName != "build");

    if (directoryName.size() > 0)
    {
        return filePath / "res" / "input" / std::format("{}", year) / std::format("Input_{}_{}.txt", year, day);
    }

    return std::filesystem::path {};
}

int Program::QueryYear()
{
    int year = 0;
    std::cout << "Enter challenge year: ";
    std::cin >> year;
    return year;
}

int Program::QueryDay()
{
    int day = 0;
    std::cout << "Enter challenge day: ";
    std::cin >> day;
    return day;
}

void Program::DisplayHelp()
{
    std::cout <<
        "AdventOfCode [-h] [-i] PATH [-y] YEAR [-d] DAY [-p1] [-p2] [-t]\n"
        "  -i   PATH  Path to a specific input file to use with the challenge program.\n"
        "  -y   YEAR  Year of the challenge program to execute.\n"
        "  -d   DAY   Day of the challenge program to execute.\n"
        "  -p1        If specified without --part2 being specified, will only run the first part of the challenge program.\n"
        "  -p2        If specified without --part1 being specified, will only run the second part of the challenge program.\n"
        "  -t         Will measure the execution time of the program, excluding argument parsing.\n"
        "  -h         Displays this message.\n"
        << std::endl;
}

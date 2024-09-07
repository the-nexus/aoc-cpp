
#pragma once

#include <filesystem>
#include <optional>
#include <string_view>
#include <vector>

namespace aoc::runtime
{
    class Program
    {
        struct Config
        {
            std::filesystem::path m_inputFilePath;
            int m_year = 0;
            int m_day = 0;
            bool m_runPartOne = false;
            bool m_runPartTwo = false;
            bool m_displayExecutionTime = false;
        };

    public:
        static int Launch(std::vector<std::string_view> const& args);

    private:
        static std::optional<Config> MakeConfig(std::vector<std::string_view> const& args);
        static std::filesystem::path GetInputFilePath(std::filesystem::path const& executionPath, int const year, int const day);
        static int QueryYear();
        static int QueryDay();
        static void DisplayHelp();
    };
}

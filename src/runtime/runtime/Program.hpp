
#pragma once

#include <filesystem>
#include <optional>
#include <string_view>
#include <vector>

namespace aoc::runtime
{
    class Program
    {
        std::filesystem::path m_exePath = {};
        std::optional<std::filesystem::path> m_inputFilePath = std::nullopt;
        std::optional<int> m_year = std::nullopt;
        std::optional<int> m_day = std::nullopt;
        std::optional<bool> m_shouldRunPartOne = std::nullopt;
        std::optional<bool> m_shouldRunPartTwo = std::nullopt;

    public:
        int Launch(std::vector<std::string_view> const& args);

    private:
        void FixArguments();
        void ParseArguments(std::vector<std::string_view> const& args);
        void PrintArgumentsHelp() const;
        std::filesystem::path GetInputFilePath(int const year, int const day) const;
    };
}

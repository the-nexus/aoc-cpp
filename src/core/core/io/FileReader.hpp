
#pragma once

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

namespace aoc::core
{
    struct FileReader
    {
        static bool GetLines(std::filesystem::path const& filePath, std::vector<std::string>& fileLines)
        {
            if (!std::filesystem::exists(filePath))
            {
                return false;
            }

            std::ifstream file { filePath };
            if (!file.is_open())
            {
                return false;
            }

            std::string line;
            while (std::getline(file, line))
            {
                fileLines.emplace_back(std::move(line));
            }

            file.close();
            return true;
        }
    };
}

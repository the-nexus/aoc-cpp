
#pragma once

#include <fstream>
#include <string>
#include <vector>

namespace AOC::Tools
{
    struct FileReader
    {
        static bool GetLines(std::string const& filePath, std::vector<std::string>& fileLines);
    };
}

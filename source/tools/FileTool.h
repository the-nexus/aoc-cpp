#pragma once

#include <fstream>
#include <string>
#include <vector>

namespace FileTool
{
    bool ReadAllLines(std::string const& filePath, std::vector<std::string>& fileLines);
}

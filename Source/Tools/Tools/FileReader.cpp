
#include "FileReader.h"

using namespace AOC::Tools;

bool FileReader::GetLines(std::string const& filePath, std::vector<std::string>& fileLines)
{
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

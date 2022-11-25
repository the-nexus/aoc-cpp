#include "FileTool.h"

namespace FileTool
{
    bool ReadAllLines(std::string const& filePath, std::vector<std::string>& fileLines)
    {
        fileLines.clear();

        std::ifstream file(filePath);
        if (file.is_open())
        {
            fileLines.push_back("");
            while (std::getline(file, fileLines[fileLines.size() - 1]))
            {
                fileLines.push_back("");
            }

            fileLines.pop_back();
            file.close();
        }

        return fileLines.size() > 0;
    }
}

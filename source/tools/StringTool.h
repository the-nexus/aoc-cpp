#pragma once

#include <string>
#include <vector>

namespace StringTool
{
    namespace
    {
        template <typename T>
        void SplitString(std::string const& stringToSplit, T const& delimiter, size_t const delimiterSize, std::vector<std::string>& outSubstrings)
        {
            size_t const stringSize = stringToSplit.size();
            size_t substringStartIndex = 0;
            size_t substringEndIndex = 0;

            while (substringStartIndex < stringSize)
            {
                size_t const delimiterIndex = stringToSplit.find(delimiter, substringStartIndex);
                substringEndIndex = delimiterIndex == std::string::npos ? stringSize : delimiterIndex;

                outSubstrings.emplace_back(stringToSplit.substr(substringStartIndex, substringEndIndex - substringStartIndex));
                substringStartIndex = substringEndIndex + delimiterSize;
            }
        }
    }

    inline void SplitString(std::string const& stringToSplit, char const delimiter, std::vector<std::string>& outSubstrings)
    {
        SplitString<char>(stringToSplit, delimiter, 1, outSubstrings);
    }

    inline void SplitString(std::string const& stringToSplit, std::string const& delimiter, std::vector<std::string>& outSubstrings)
    {
        SplitString<std::string>(stringToSplit, delimiter, delimiter.size(), outSubstrings);
    }
}

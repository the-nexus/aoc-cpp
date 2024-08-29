
#pragma once

#include <iostream>
#include <string>
#include <string_view>

namespace aoc::core
{
    struct StringViewConverter
    {
        template<typename T>
        static T ToInteger(std::string_view const& view)
        {
            T value = 0;
            for (char c : view)
            {
                value = value * 10 + static_cast<T>(c - '0');
            }
            return value;
        }
    };
}
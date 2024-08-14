
#pragma once

#include "Tools/Challenges/Challenge.hpp"

namespace AOC::Tools
{
    template <unsigned int N_YEAR, unsigned int N_DAY>
    class ChallengeImpl : public Challenge
    {
    public:
        constexpr unsigned int GetYear() const { return N_YEAR; }
        constexpr unsigned int GetDay() const { return N_DAY; }
    };
}

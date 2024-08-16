
#pragma once

#include "Factory.hpp"

namespace AOC::Tools
{
    class Challenge : public Factory<Challenge>
    {
    public:
        Challenge(Permit permit) : Factory<Challenge>(permit) {}
    };
}
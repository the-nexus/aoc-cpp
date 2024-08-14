
#pragma once

#include "Tools/Challenges/Challenge.hpp"
#include "Tools/Utilities/Factory.hpp"

namespace AOC::Tools
{
    class ChallengeFactory : public Factory<std::pair<unsigned int, unsigned int>, Challenge>
    {
        
    };
}

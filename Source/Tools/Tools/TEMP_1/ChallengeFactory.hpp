
#pragma once

#include "Challenge.hpp"
#include "ChallengeIdentifier.hpp"
#include "Factory.hpp"

namespace AOC::Tools
{
    class ChallengeFactory : public Factory<ChallengeIdentifier, Challenge>
    {
        
    };
}

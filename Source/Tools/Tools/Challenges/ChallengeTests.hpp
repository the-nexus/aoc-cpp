#pragma once

#include <tuple>

#include "Tools/Challenges/Challenge.hpp"
#include "Tools/Challenges/ChallengeFactory.hpp"

namespace AOC::Tools
{
    struct ChallengeTests
    {
        static void Run()
        {
            ChallengeFactory::Produce({2020, 11});
        }
    };
}

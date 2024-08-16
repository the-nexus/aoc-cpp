#pragma once

#include <iostream>

#include "Challenge_2020_11.hpp"

#include "ChallengeFactory.hpp"

namespace AOC::Tools::Tests
{
    void Run()
    {
        std::cout << "Producing:\n";
        if (ChallengeFactory::Produce({2020, 10})) std::cout << "2020-10 was produced\n";
        if (ChallengeFactory::Produce({2020, 11})) std::cout << "2020-11 was produced\n";
        if (ChallengeFactory::Produce({2020, 12})) std::cout << "2020-12 was produced\n";
    }
}

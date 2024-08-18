
#pragma once

#include <Tools/Utilities/Challenge.hpp>
#include <Tools/Utilities/Factory.hpp>

namespace AOC::Challenges
{
    class Factory : public Tools::Factory<Tools::ChallengeID, Tools::IChallenge, std::vector<std::string>>
    {
        static void RegisterAllChallenges();
    };
}

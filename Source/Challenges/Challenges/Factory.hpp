
#pragma once

#include <Tools/Utilities/Factory.hpp>

#include "Challenges/Challenge.hpp"

#if __has_include("Challenges/Autogen/Factory.autogen.inl")
#include "Challenges/Autogen/Factory.autogen.inl"
#endif

namespace AOC::Challenges
{
    class Factory : public Tools::Factory<ChallengeIdentifier, IChallenge, std::vector<std::string>>
    {
    private:
        template <typename ChallengeT>
        static void RegisterChallenge()
        {
            RegisterProduct(ChallengeT::GetIdentifier(), [](std::vector<std::string>&& input)
            {
                return std::make_unique<ChallengeT>(std::move(input));
            });
        }

    public:
        static void RegisterAll()
        {
#ifdef AUTOGEN_CHALLENGE_REGISTRY
            AUTOGEN_CHALLENGE_REGISTRY
#endif // AUTOGEN_CHALLENGE_REGISTRY
        }
    };
}


#pragma once

#include <core/generation/Factory.hpp>

#include "challenges/Challenge.hpp"

#if __has_include("challenges/autogen/Factory.autogen.inl")
#include "challenges/autogen/Factory.autogen.inl"
#endif

namespace aoc::challenges
{
    class Factory final : public core::Factory<ChallengeIdentifier, IChallenge, std::vector<std::string>>
    {
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

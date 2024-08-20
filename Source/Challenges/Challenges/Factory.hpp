
#pragma once

#include <Tools/Utilities/Challenge.hpp>
#include <Tools/Utilities/Factory.hpp>

namespace AOC::Challenges
{
    class Factory : public Tools::Factory<Tools::ChallengeID, Tools::IChallenge, std::vector<std::string>>
    {
    public:
        static void RegisterAll();

    private:
        template <typename ChallengeT>
        static void RegisterChallenge()
        {
            RegisterProduct(ChallengeT::GetID(), [](std::vector<std::string>&& input) { return std::make_unique<ChallengeT>(std::move(input)); });
        }
    };
}

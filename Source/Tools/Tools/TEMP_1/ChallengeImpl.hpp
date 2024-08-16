
#pragma once

#include "Challenge.hpp"
#include "ChallengeFactory.hpp"

namespace AOC::Tools
{
    template <unsigned int N_YEAR, unsigned int N_DAY>
    class ChallengeImpl : public Challenge
    {
    private:
        static bool sm_isRegistered;
    };

    template <unsigned int N_YEAR, unsigned int N_DAY>
    bool ChallengeImpl<N_YEAR, N_DAY>::sm_isRegistered = ChallengeFactory::Register(
        { N_YEAR, N_DAY }, []() { return new ChallengeImpl<N_YEAR, N_DAY>(); }
    );
}

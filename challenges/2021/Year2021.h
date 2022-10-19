
#include "Challenge01.h"

namespace ChallengeFactory
{
    namespace Year2021
    {
        ChallengeAbstract* MakeChallenge(int const day)
        {
            switch (day)
            {
            case 01: return new Challenge01();
            default: return nullptr;
            }
        }
    }
}


#include "ChallengeAbstract.h"
#include "2021/Year2021.h"

namespace ChallengeFactory
{
    ChallengeAbstract* MakeChallenge(int const year, int const day)
    {
        switch (year)
        {
        case 2021: return Year2021::MakeChallenge(day);
        default: return nullptr;
        }
    }
}

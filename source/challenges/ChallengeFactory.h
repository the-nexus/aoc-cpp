
// ================================================================================================
// Edit this file when starting a new year to add a copy of the commented include and case line
// Replace 'XXXX' in those lines with the year of the challenges
// ================================================================================================

//#include "XXXX/YearXXXX.h"
#include "2021/Year2021.h"
#include "ChallengeAbstract.h"

namespace ChallengeFactory
{
    ChallengeAbstract* MakeChallenge(int const year, int const day)
    {
        switch (year)
        {
        //case XXXX: return YearXXXX::MakeChallenge(day);
        case 2021: return Year2021::MakeChallenge(day);
        default: return nullptr;
        }
    }
}

#pragma once

#include <memory>
#include <string>
#include <vector>

// ================================================================================================
// Edit this file when starting a new year to add a copy of the commented include and case line
// Replace 'XXXX' in those lines with the year of the challenges
// ================================================================================================

//#include "XXXX/YearXXXX.h"
#include "2018/Year2018.h"
#include "2021/Year2021.h"
#include "2022/Year2022.h"
#include "2023/Year2023.h"
#include "ChallengeAbstract.h"

namespace ChallengeFactory
{
    std::unique_ptr<ChallengeAbstract> MakeChallenge(int const year, int const day, std::shared_ptr<std::vector<std::string>> const& inputLines)
    {
        switch (year)
        {
        //case XXXX: return YearXXXX::MakeChallenge(day, inputLines);
        case 2018: return Year2018::MakeChallenge(day, inputLines);
        case 2021: return Year2021::MakeChallenge(day, inputLines);
        case 2022: return Year2022::MakeChallenge(day, inputLines);
        case 2023: return Year2023::MakeChallenge(day, inputLines);
        default: return nullptr;
        }
    }
}

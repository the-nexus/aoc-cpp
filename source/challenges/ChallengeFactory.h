#pragma once

#include <memory>

// ================================================================================================
// Edit this file when starting a new year to add a copy of the commented include and case line
// Replace 'XXXX' in those lines with the year of the challenges
// ================================================================================================

//#include "XXXX/YearXXXX.h"
#include "2015/Year2015.h"
#include "2016/Year2016.h"
#include "2017/Year2017.h"
#include "2018/Year2018.h"
#include "2019/Year2019.h"
#include "2020/Year2020.h"
#include "2021/Year2021.h"
#include "2022/Year2022.h"
#include "2023/Year2023.h"
#include "ChallengeAbstract.h"

namespace ChallengeFactory
{
    std::unique_ptr<ChallengeAbstract> MakeChallenge(int const year, int const day)
    {
        switch (year)
        {
        //case XXXX: return YearXXXX::MakeChallenge(day);
        case 2015: return Year2015::MakeChallenge(day);
        case 2016: return Year2016::MakeChallenge(day);
        case 2017: return Year2017::MakeChallenge(day);
        case 2018: return Year2018::MakeChallenge(day);
        case 2019: return Year2019::MakeChallenge(day);
        case 2020: return Year2020::MakeChallenge(day);
        case 2021: return Year2021::MakeChallenge(day);
        case 2022: return Year2022::MakeChallenge(day);
        case 2023: return Year2023::MakeChallenge(day);
        default: return nullptr;
        }
    }
}


#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Challenge01.h"
#include "Challenge02.h"
//#include "Challenge03.h"
//#include "Challenge04.h"
//#include "Challenge05.h"
//#include "Challenge06.h"
//#include "Challenge07.h"
//#include "Challenge08.h"
//#include "Challenge09.h"
//#include "Challenge10.h"
//#include "Challenge11.h"
//#include "Challenge12.h"
//#include "Challenge13.h"
//#include "Challenge14.h"
//#include "Challenge15.h"
//#include "Challenge16.h"
//#include "Challenge17.h"
//#include "Challenge18.h"
//#include "Challenge19.h"
//#include "Challenge20.h"
//#include "Challenge21.h"
//#include "Challenge23.h"
//#include "Challenge24.h"
//#include "Challenge25.h"
//#include "Challenge26.h"

namespace AOC::Challenges::Year2021
{
    std::unique_ptr<ChallengeAbstract> MakeChallenge(int const day, std::vector<std::string> const& inputLines)
    {
        switch (day)
        {
        case 1:  return std::make_unique<Challenge01>(inputLines);
        case 2:  return std::make_unique<Challenge02>(inputLines);
        //case 3:  return std::make_unique<Challenge03>(inputLines);
        //case 4:  return std::make_unique<Challenge04>(inputLines);
        //case 5:  return std::make_unique<Challenge05>(inputLines);
        //case 6:  return std::make_unique<Challenge06>(inputLines);
        //case 7:  return std::make_unique<Challenge07>(inputLines);
        //case 8:  return std::make_unique<Challenge08>(inputLines);
        //case 9:  return std::make_unique<Challenge09>(inputLines);
        //case 10: return std::make_unique<Challenge10>(inputLines);
        //case 11: return std::make_unique<Challenge11>(inputLines);
        //case 12: return std::make_unique<Challenge12>(inputLines);
        //case 13: return std::make_unique<Challenge13>(inputLines);
        //case 14: return std::make_unique<Challenge14>(inputLines);
        //case 15: return std::make_unique<Challenge15>(inputLines);
        //case 16: return std::make_unique<Challenge16>(inputLines);
        //case 17: return std::make_unique<Challenge17>(inputLines);
        //case 18: return std::make_unique<Challenge18>(inputLines);
        //case 19: return std::make_unique<Challenge19>(inputLines);
        //case 20: return std::make_unique<Challenge21>(inputLines);
        //case 21: return std::make_unique<Challenge22>(inputLines);
        //case 22: return std::make_unique<Challenge23>(inputLines);
        //case 23: return std::make_unique<Challenge24>(inputLines);
        //case 24: return std::make_unique<Challenge25>(inputLines);
        //case 25: return std::make_unique<Challenge26>(inputLines);
        default: return nullptr;
        }
    }
}

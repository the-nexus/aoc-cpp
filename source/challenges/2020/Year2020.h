#pragma once

#include <memory>

#include "../templates/ChallengeTemplate.h"

#if __has_include("Challenge01.h")
#include "Challenge01.h"
#define CHALLENGE_01 std::make_unique<Challenge01>()
#else
#define CHALLENGE_01 nullptr
#endif

#if __has_include("Challenge02.h")
#include "Challenge02.h"
#define CHALLENGE_02 std::make_unique<Challenge02>()
#else
#define CHALLENGE_02 nullptr
#endif

#if __has_include("Challenge03.h")
#include "Challenge03.h"
#define CHALLENGE_03 std::make_unique<Challenge03>()
#else
#define CHALLENGE_03 nullptr
#endif

#if __has_include("Challenge04.h")
#include "Challenge04.h"
#define CHALLENGE_04 std::make_unique<Challenge04>()
#else
#define CHALLENGE_04 nullptr
#endif

#if __has_include("Challenge05.h")
#include "Challenge05.h"
#define CHALLENGE_05 std::make_unique<Challenge05>()
#else
#define CHALLENGE_05 nullptr
#endif

#if __has_include("Challenge06.h")
#include "Challenge06.h"
#define CHALLENGE_06 std::make_unique<Challenge06>()
#else
#define CHALLENGE_06 nullptr
#endif

#if __has_include("Challenge07.h")
#include "Challenge07.h"
#define CHALLENGE_07 std::make_unique<Challenge07>()
#else
#define CHALLENGE_07 nullptr
#endif

#if __has_include("Challenge08.h")
#include "Challenge08.h"
#define CHALLENGE_08 std::make_unique<Challenge08>()
#else
#define CHALLENGE_08 nullptr
#endif

#if __has_include("Challenge09.h")
#include "Challenge09.h"
#define CHALLENGE_09 std::make_unique<Challenge09>()
#else
#define CHALLENGE_09 nullptr
#endif

#if __has_include("Challenge10.h")
#include "Challenge10.h"
#define CHALLENGE_10 std::make_unique<Challenge10>()
#else
#define CHALLENGE_10 nullptr
#endif

#if __has_include("Challenge11.h")
#include "Challenge11.h"
#define CHALLENGE_11 std::make_unique<Challenge11>()
#else
#define CHALLENGE_11 nullptr
#endif

#if __has_include("Challenge12.h")
#include "Challenge12.h"
#define CHALLENGE_12 std::make_unique<Challenge12>()
#else
#define CHALLENGE_12 nullptr
#endif

#if __has_include("Challenge13.h")
#include "Challenge13.h"
#define CHALLENGE_13 std::make_unique<Challenge13>()
#else
#define CHALLENGE_13 nullptr
#endif

#if __has_include("Challenge14.h")
#include "Challenge14.h"
#define CHALLENGE_14 std::make_unique<Challenge14>()
#else
#define CHALLENGE_14 nullptr
#endif

#if __has_include("Challenge15.h")
#include "Challenge15.h"
#define CHALLENGE_15 std::make_unique<Challenge15>()
#else
#define CHALLENGE_15 nullptr
#endif

#if __has_include("Challenge16.h")
#include "Challenge16.h"
#define CHALLENGE_16 std::make_unique<Challenge16>()
#else
#define CHALLENGE_16 nullptr
#endif

#if __has_include("Challenge17.h")
#include "Challenge17.h"
#define CHALLENGE_17 std::make_unique<Challenge17>()
#else
#define CHALLENGE_17 nullptr
#endif

#if __has_include("Challenge18.h")
#include "Challenge18.h"
#define CHALLENGE_18 std::make_unique<Challenge18>()
#else
#define CHALLENGE_18 nullptr
#endif

#if __has_include("Challenge19.h")
#include "Challenge19.h"
#define CHALLENGE_19 std::make_unique<Challenge19>()
#else
#define CHALLENGE_19 nullptr
#endif

#if __has_include("Challenge20.h")
#include "Challenge20.h"
#define CHALLENGE_20 std::make_unique<Challenge20>()
#else
#define CHALLENGE_20 nullptr
#endif

#if __has_include("Challenge21.h")
#include "Challenge21.h"
#define CHALLENGE_21 std::make_unique<Challenge21>()
#else
#define CHALLENGE_21 nullptr
#endif

#if __has_include("Challenge22.h")
#include "Challenge22.h"
#define CHALLENGE_22 std::make_unique<Challenge22>()
#else
#define CHALLENGE_22 nullptr
#endif

#if __has_include("Challenge23.h")
#include "Challenge23.h"
#define CHALLENGE_23 std::make_unique<Challenge23>()
#else
#define CHALLENGE_23 nullptr
#endif

#if __has_include("Challenge24.h")
#include "Challenge24.h"
#define CHALLENGE_24 std::make_unique<Challenge24>()
#else
#define CHALLENGE_24 nullptr
#endif

#if __has_include("Challenge25.h")
#include "Challenge25.h"
#define CHALLENGE_25 std::make_unique<Challenge25>()
#else
#define CHALLENGE_25 nullptr
#endif

namespace Year2020
{
    std::unique_ptr<ChallengeAbstract> MakeChallenge(int const day)
    {
        switch (day)
        {
        case 1: return CHALLENGE_01;
        case 2: return CHALLENGE_02;
        case 3: return CHALLENGE_03;
        case 4: return CHALLENGE_04;
        case 5: return CHALLENGE_05;
        case 6: return CHALLENGE_06;
        case 7: return CHALLENGE_07;
        case 8: return CHALLENGE_08;
        case 9: return CHALLENGE_09;
        case 10: return CHALLENGE_10;
        case 11: return CHALLENGE_11;
        case 12: return CHALLENGE_12;
        case 13: return CHALLENGE_13;
        case 14: return CHALLENGE_14;
        case 15: return CHALLENGE_15;
        case 16: return CHALLENGE_16;
        case 17: return CHALLENGE_17;
        case 18: return CHALLENGE_18;
        case 19: return CHALLENGE_19;
        case 20: return CHALLENGE_20;
        case 21: return CHALLENGE_21;
        case 22: return CHALLENGE_22;
        case 23: return CHALLENGE_23;
        case 24: return CHALLENGE_24;
        case 25: return CHALLENGE_25;
        default: return nullptr;
        }
    }
}

#undef CHALLENGE_01
#undef CHALLENGE_02
#undef CHALLENGE_03
#undef CHALLENGE_04
#undef CHALLENGE_05
#undef CHALLENGE_06
#undef CHALLENGE_07
#undef CHALLENGE_08
#undef CHALLENGE_09
#undef CHALLENGE_10
#undef CHALLENGE_11
#undef CHALLENGE_12
#undef CHALLENGE_13
#undef CHALLENGE_14
#undef CHALLENGE_15
#undef CHALLENGE_16
#undef CHALLENGE_17
#undef CHALLENGE_18
#undef CHALLENGE_19
#undef CHALLENGE_20
#undef CHALLENGE_21
#undef CHALLENGE_22
#undef CHALLENGE_23
#undef CHALLENGE_24
#undef CHALLENGE_25

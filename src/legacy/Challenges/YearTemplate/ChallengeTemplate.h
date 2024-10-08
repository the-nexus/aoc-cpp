
#pragma once

#include "../ChallengeAbstract.h"

namespace AOC::Challenges::YearTemplate
{
    class ChallengeTemplate final : public ChallengeAbstract
    {
    public:
        ChallengeTemplate(std::shared_ptr<std::vector<std::string>> const& inputLines)
        {

        }

        virtual void Run_PartOne() override
        {
            ChallengeAbstract::Run_PartOne();
        }

        virtual void Run_PartTwo() override
        {
            ChallengeAbstract::Run_PartTwo();
        }
    };
}

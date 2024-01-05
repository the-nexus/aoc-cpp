#pragma once

#include "../ChallengeAbstract.h"

namespace Year2023
{
    class Challenge06 : public ChallengeAbstract
    {
    private:
        struct Race
        {
            int m_durationMS = 0;
            int m_distanceMM = 0;
        };

        std::vector<Race> m_races;

    public:
        virtual void SetUp(std::vector<std::string> const& inputLines) override
        {
            int value = 0;
            for (char const token : inputLines[0])
            {
                if (token >= '0' && token <= '9')
                {
                    value = value * 10 + static_cast<int>(token - '0');
                }
                else if (value > 0)
                {
                    Race& race = m_races.emplace_back();
                    race.m_durationMS = value;
                    value = 0;
                }
            }

            if (value > 0)
            {
                Race& race = m_races.emplace_back();
                race.m_durationMS = value;
                value = 0;
            }

            auto it = m_races.begin();
            for (char const token : inputLines[1])
            {
                if (token >= '0' && token <= '9')
                {
                    value = value * 10 + static_cast<int>(token - '0');
                }
                else if (value > 0)
                {
                    it->m_distanceMM = value;
                    value = 0;
                    ++it;
                }
            }

            if (value > 0)
            {
                it->m_distanceMM = value;
            }
        }

        virtual void Run_PartOne() override
        {
            int product = 1;

            for (Race const& race : m_races)
            {
                int winners = CountWinners(race);
                product *= winners;
            }

            std::cout << product << std::endl;
        }

        virtual void Run_PartTwo() override
        {
            Race newRace;
            for (Race oldRace : m_races)
            {

            }

            std::cout << CountWinners(newRace) << std::endl;
        }

        virtual void CleanUp() override {}

    private:
        static int CountWinners(Race const& race)
        {
            int const startTime = static_cast<int>(roundf(race.m_durationMS * 0.5f));
            int const firstTime = FindFirstWinner(race, startTime, race.m_durationMS / 2);
            int const wins = race.m_durationMS - 2 * (firstTime);

            std::cout << "Wins=" << wins << std::endl;
            return wins;
        }

        static int FindFirstWinner(Race const& race, int const currentTime, int timeRange)
        {
            if (timeRange <= 0)
            {
                return currentTime;
            }

            timeRange /= 2;
            int const distanceMM = (race.m_durationMS - currentTime) * currentTime;

            if (distanceMM > race.m_distanceMM)
            {
                return FindFirstWinner(race, currentTime - timeRange, timeRange);
            }
            else
            {
                return FindFirstWinner(race, currentTime + timeRange, timeRange);
            }
        }
    };
}

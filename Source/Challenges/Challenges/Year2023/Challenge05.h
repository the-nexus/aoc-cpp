
#pragma once

#include "Challenges/ChallengeAbstract.h"

namespace AOC::Challenges::Year2023
{
    class Challenge05 final : public ChallengeAbstract
    {
    private:
        typedef long long SEED_TYPE;

        struct Range
        {
            SEED_TYPE m_srcStart = 0;
            SEED_TYPE m_dstStart = 0;
            SEED_TYPE m_size = 0;
        };

        struct Map
        {
            std::vector<Range> m_ranges;
        };

        std::vector<Map> m_maps;
        std::vector<SEED_TYPE> m_seeds;

    public:
        Challenge05(std::vector<std::string> const& inputLines)
        {
            auto it = inputLines.cbegin();

            if (it != inputLines.cend())
            {
                size_t const seedPos = it->find_first_of(' ') + 1;
                std::vector<std::string> seedSplit;
                Tools::StringSplitter::SplitString(it->substr(seedPos), ' ', seedSplit);

                m_seeds.reserve(seedSplit.size());
                for (std::string const& seedStr : seedSplit)
                {
                    m_seeds.push_back(atoll(seedStr.c_str()));
                }
            }

            Map* map = nullptr;
            for (++it; it != inputLines.cend(); ++it)
            {
                if (it->empty())
                {
                    map = &m_maps.emplace_back();
                    continue;
                }

                if (it->back() == ':')
                {
                    continue;
                }

                if (!map)
                    break;

                std::vector<std::string> rangeSplit;
                Tools::StringSplitter::SplitString(*it, ' ', rangeSplit);

                Range& range = map->m_ranges.emplace_back();
                range.m_dstStart = atoll(rangeSplit[0].c_str());
                range.m_srcStart = atoll(rangeSplit[1].c_str());
                range.m_size = atoll(rangeSplit[2].c_str());
            }
        }

        virtual void Run_PartOne() override
        {
            SEED_TYPE lowestLocation = LLONG_MAX;

            for (SEED_TYPE const seed : m_seeds)
            {
                SEED_TYPE const location = FindLocation(seed);
                if (location < lowestLocation)
                {
                    lowestLocation = location;
                }
            }

            std::cout << lowestLocation << std::endl;
        }

        virtual void Run_PartTwo() override
        {
            SEED_TYPE lowestLocation = LLONG_MAX;

            for (size_t seedIndex = 0; seedIndex < m_seeds.size() - 1; seedIndex += 2)
            {
                for (SEED_TYPE seedOffset = 0; seedOffset < m_seeds[seedIndex + 1]; ++seedOffset)
                {
                    SEED_TYPE const location = FindLocation(m_seeds[seedIndex] + seedOffset);
                    if (location < lowestLocation)
                    {
                        lowestLocation = location;
                    }
                }
            }

            std::cout << lowestLocation << std::endl;
        }

    private:
        SEED_TYPE FindLocation(SEED_TYPE seed) const
        {
            for (Map const& map : m_maps)
            {
                seed = Remap(map, seed);
            }

            return seed;
        }

        static SEED_TYPE Remap(Map const& map, SEED_TYPE const seed)
        {
            for (Range const& range : map.m_ranges)
            {
                if (seed >= range.m_srcStart && seed < range.m_srcStart + range.m_size)
                {
                    return seed - range.m_srcStart + range.m_dstStart;
                }
            }

            return seed;
        }
    };
}


#pragma once

#include "challenges/Challenge.hpp"

#include <algorithm>

namespace aoc::challenges
{
    class Challenge_2025_5 final : public Challenge<2025, 5>
    {
        using Super = Challenge<2025, 5>;

    public:
        Challenge_2025_5(std::vector<std::string>&& inputLines)
            : Super(std::move(inputLines))
        {}

        void RunPartOne(std::ostream& outAnswer) override
        {
            const std::vector<std::string>& lines = GetInputLines();
            auto lineIt = std::cbegin(lines);

            std::vector<std::pair<unsigned long long, unsigned long long>> idRanges;
            idRanges.reserve(lines.size());

            for (; lineIt != std::cend(lines); ++lineIt)
            {
                if (lineIt->empty())
                {
                    break;
                }

                const auto separatorIt = lineIt->find('-');

                std::pair<unsigned long long, unsigned long long>& newIdRange = idRanges.emplace_back();
                newIdRange.first = std::stoull(lineIt->substr(0, separatorIt));
                newIdRange.second = std::stoull(lineIt->substr(separatorIt + 1));
            }

            std::vector<unsigned long long> ingredients;
            ingredients.reserve(lines.size() - idRanges.size());

            for (++lineIt; lineIt != std::cend(lines); ++lineIt)
            {
                ingredients.push_back(std::stoull(*lineIt));
            }

            int freshCount = 0;
            for (const unsigned long long ingredient : ingredients)
            {
                const auto it = std::find_if(std::cbegin(idRanges), std::cend(idRanges), [&ingredient](const std::pair<unsigned long long, unsigned long long>& idRange)
                {
                    return ingredient >= idRange.first && ingredient <= idRange.second;
                });

                if (it != std::cend(idRanges))
                {
                    ++freshCount;
                }
            }

            outAnswer << freshCount;
        }

        void RunPartTwo(std::ostream& outAnswer) override
        {
            const std::vector<std::string>& lines = GetInputLines();
            auto lineIt = std::cbegin(lines);

            std::vector<std::pair<unsigned long long, unsigned long long>> idRanges;
            idRanges.reserve(lines.size());

            for (; lineIt != std::cend(lines); ++lineIt)
            {
                if (lineIt->empty())
                {
                    break;
                }

                const auto separatorIt = lineIt->find('-');

                std::pair<unsigned long long, unsigned long long>& newIdRange = idRanges.emplace_back();
                newIdRange.first = std::stoull(lineIt->substr(0, separatorIt));
                newIdRange.second = std::stoull(lineIt->substr(separatorIt + 1));
            }

            // Merge ranges


            int freshCount = 0;

            // Sum differences of ranges (inclusively)

            outAnswer << freshCount;
        }
    };
}

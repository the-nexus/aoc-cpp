
#pragma once

#include "challenges/Challenge.hpp"

#include <charconv>
#include <string_view>

namespace aoc::challenges
{
    class Challenge_2024_1 final : public Challenge<2024, 1>
    {
        using Super = Challenge<2024, 1>;

    public:
        Challenge_2024_1(std::vector<std::string>&& inputLines)
            : Super(std::move(inputLines))
        {}

        void RunPartOne(std::ostream& outAnswer) override
        {
            std::vector<unsigned int> leftIDs, rightIDs;
            AssembleLists(leftIDs, rightIDs);

            std::sort(std::begin(leftIDs), std::end(leftIDs));
            std::sort(std::begin(rightIDs), std::end(rightIDs));

            unsigned int differenceSum = 0u;
            for (size_t idIndex = 0u; idIndex < leftIDs.size(); ++idIndex)
            {
                unsigned int const leftID = leftIDs[idIndex];
                unsigned int const rightID = rightIDs[idIndex];

                if (leftID < rightID)
                {
                    differenceSum += rightID - leftID;
                }
                else
                {
                    differenceSum += leftID - rightID;
                }
            }

            outAnswer << differenceSum;
        }

        void RunPartTwo(std::ostream& outAnswer) override
        {
            std::vector<unsigned int> leftIDs, rightIDs;
            AssembleLists(leftIDs, rightIDs);

            std::map<unsigned int, unsigned int> rightOccurences;
            MapOccurences(rightIDs, rightOccurences);

            unsigned int similarityScore = 0u;
            for (unsigned int const identifier : leftIDs)
            {
                auto const it = rightOccurences.find(identifier);
                if (it != rightOccurences.cend())
                {
                    similarityScore += identifier * it->second;
                }
            }

            outAnswer << similarityScore;
        }

        void AssembleLists(std::vector<unsigned int>& outLeftIDs, std::vector<unsigned int>& outRightIDs) const
        {
            std::vector<std::string> const& lines = GetInputLines();

            outLeftIDs.resize(lines.size());
            outRightIDs.resize(lines.size());

            for (size_t idIndex = 0u; idIndex < outLeftIDs.size(); ++idIndex)
            {
                std::string const& line = lines[idIndex];
                size_t const delimiterPosition = line.find(' ');

                outLeftIDs[idIndex] = std::stoul(line.substr(0u, delimiterPosition));
                outRightIDs[idIndex] = std::stoul(line.substr(delimiterPosition + 3u));
            }
        }

        void MapOccurences(std::vector<unsigned int> const& identifiers, std::map<unsigned int, unsigned int>& outOccurences)
        {
            for (unsigned int const identifier : identifiers)
            {
                auto result = outOccurences.try_emplace(identifier, 0u);
                ++(result.first->second);
            }
        }
    };
}

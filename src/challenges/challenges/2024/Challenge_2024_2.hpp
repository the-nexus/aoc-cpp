
#pragma once

#include "challenges/Challenge.hpp"

#include <algorithm>

namespace aoc::challenges
{
    class Challenge_2024_2 final : public Challenge<2024, 2>
    {
        using Super = Challenge<2024, 2>;

    public:
        Challenge_2024_2(std::vector<std::string>&& inputLines)
            : Super(std::move(inputLines))
        {}

        void RunPartOne(std::ostream& outAnswer) override
        {
            std::vector<std::vector<unsigned int>> reports;
            AssembleReports(reports);

            unsigned int safeReportCount = 0u;
            for (std::vector<unsigned int> const& report : reports)
            {
                if (IsSafeReport(report, 0u))
                {
                    ++safeReportCount;
                }
            }

            outAnswer << safeReportCount;
        }

        void RunPartTwo(std::ostream& outAnswer) override
        {
            std::vector<std::vector<unsigned int>> reports;
            AssembleReports(reports);

            unsigned int safeReportCount = 0u;
            for (std::vector<unsigned int> const& report : reports)
            {
                if (IsSafeReport(report, 1u))
                {
                    ++safeReportCount;
                }
            }

            outAnswer << safeReportCount;
        }

        void AssembleReports(std::vector<std::vector<unsigned int>>& outReports)
        {
            outReports.reserve(GetInputLines().size());
            for (std::string const& line : GetInputLines())
            {
                size_t const separatorCount = std::count(std::cbegin(line), std::cend(line), ' ');
                std::vector<unsigned int>& report = outReports.emplace_back();
                report.reserve(separatorCount + 1u);

                unsigned int level = 0u;
                for (char const token : line)
                {
                    if (token == ' ')
                    {
                        report.push_back(level);
                        level = 0u;
                    }
                    else
                    {
                        level = level * 10u + static_cast<unsigned int>(token - '0');
                    }
                }

                report.push_back(level);
            }
        }

        bool IsSafeReport(std::vector<unsigned int> const& report, unsigned int const maxAllowedAberrations) const
        {
            if (report.size() == 0u)
            {
                return false;
            }

            auto const startIt = std::cbegin(report);
            auto const endIt = std::cend(report);
            auto const nextIt = startIt + 1;

            if (AreAllLevelsIncreasing(nextIt, endIt, *startIt, maxAllowedAberrations))
            {
                return true;
            }

            if (AreAllLevelsDecreasing(nextIt, endIt, *startIt, maxAllowedAberrations))
            {
                return true;
            }

            if (maxAllowedAberrations == 0u || report.size() == 1u)
            {
                return false;
            }

            if (AreAllLevelsIncreasing(nextIt + 1, endIt, *nextIt, maxAllowedAberrations - 1u))
            {
                return true;
            }

            if (AreAllLevelsDecreasing(nextIt + 1, endIt, *nextIt, maxAllowedAberrations - 1u))
            {
                return true;
            }

            return false;

        }

        bool AreAllLevelsIncreasing(auto const& startIt, auto const& endIt, unsigned int const lastLevel, unsigned int const maxAllowedAberrations) const
        {
            if (startIt == endIt)
            {
                return true;
            }

            unsigned int const currentLevel = *startIt;
            if (currentLevel <= lastLevel)
            {
                if (maxAllowedAberrations > 0u)
                {
                    return AreAllLevelsIncreasing(startIt + 1, endIt, lastLevel, maxAllowedAberrations - 1u);
                }

                return false;
            }

            unsigned int const delta = currentLevel - lastLevel;
            if (delta < 1u || delta > 3u)
            {
                if (maxAllowedAberrations > 0u)
                {
                    return AreAllLevelsIncreasing(startIt + 1, endIt, lastLevel, maxAllowedAberrations - 1u);
                }

                return false;
            }

            return AreAllLevelsIncreasing(startIt + 1, endIt, currentLevel, maxAllowedAberrations);
        }

        bool AreAllLevelsDecreasing(auto const& startIt, auto const& endIt, unsigned int const lastLevel, unsigned int const maxAllowedAberrations) const
        {
            if (startIt == endIt)
            {
                return true;
            }

            unsigned int const currentLevel = *startIt;
            if (currentLevel >= lastLevel)
            {
                if (maxAllowedAberrations > 0u)
                {
                    return AreAllLevelsDecreasing(startIt + 1, endIt, lastLevel, maxAllowedAberrations - 1u);
                }

                return false;
            }

            unsigned int const delta = lastLevel - currentLevel;
            if (delta < 1u || delta > 3u)
            {
                if (maxAllowedAberrations > 0u)
                {
                    return AreAllLevelsDecreasing(startIt + 1, endIt, lastLevel, maxAllowedAberrations - 1u);
                }

                return false;
            }

            return AreAllLevelsDecreasing(startIt + 1, endIt, currentLevel, maxAllowedAberrations);
        }
    };
}

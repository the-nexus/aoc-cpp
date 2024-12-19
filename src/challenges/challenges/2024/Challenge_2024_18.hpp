
#pragma once

#include "challenges/Challenge.hpp"

#include <algorithm>
#include <set>

#include <core/containers/Grid.hpp>

namespace aoc::challenges
{
    class Challenge_2024_18 final : public Challenge<2024, 18>
    {
        using Super = Challenge<2024, 18>;
        using Coordinates = std::pair<size_t, size_t>;

        static size_t constexpr _gridSize = 71u;
        static size_t constexpr _uniquePositionCount = _gridSize * _gridSize;
        static size_t constexpr _corruptedTileValue = std::numeric_limits<size_t>::max();
        static Coordinates constexpr _startPosition = { 0u, 0u };
        static Coordinates constexpr _endPosition = { _gridSize - 1u, _gridSize - 1u };

    public:
        Challenge_2024_18(std::vector<std::string>&& inputLines)
            : Super(std::move(inputLines))
        {}

        void RunPartOne(std::ostream& outAnswer) override
        {
            std::vector<Coordinates> corruptedPositions;
            ReadCorruptedCoordinates(corruptedPositions);

            core::Grid<size_t> tileGrid = { _gridSize, _gridSize };
            tileGrid.SetAll(_uniquePositionCount);

            size_t const maxIndex = corruptedPositions.size() < 1024u ? corruptedPositions.size() : 1024u;
            for (size_t corruptedPositionIndex = 0u; corruptedPositionIndex < maxIndex; ++corruptedPositionIndex)
            {
                Coordinates const& corruptedPosition = corruptedPositions[corruptedPositionIndex];
                tileGrid.WriteAt(corruptedPosition.first, corruptedPosition.second) = _corruptedTileValue;
            }

            outAnswer << MeasureShortestPath(tileGrid);
        }

        void RunPartTwo(std::ostream& outAnswer) override
        {
            std::vector<Coordinates> corruptedPositions;
            ReadCorruptedCoordinates(corruptedPositions);

            core::Grid<size_t> tileGrid = { _gridSize, _gridSize };
            tileGrid.SetAll(_uniquePositionCount);

            size_t steps = 0u;
            for (; steps < corruptedPositions.size(); ++steps)
            {
                std::cout << steps << '\n';
                if (MeasureShortestPath(tileGrid) >= _uniquePositionCount)
                {
                    break;
                }

                Coordinates const& corruptedPosition = corruptedPositions[steps];
                tileGrid.WriteAt(corruptedPosition.first, corruptedPosition.second) = _corruptedTileValue;
            }

            outAnswer << steps;
        }

        void ReadCorruptedCoordinates(std::vector<Coordinates>& outCorruptedPositions) const
        {
            std::vector<std::string> const& lines = GetInputLines();
            outCorruptedPositions.resize(lines.size());
            for (size_t lineIndex = 0u; lineIndex < lines.size(); ++lineIndex)
            {
                std::string const& line = lines[lineIndex];
                size_t const separatorIndex = line.find(',');

                Coordinates& position = outCorruptedPositions[lineIndex];
                position.first = std::stoul(line.substr(0u, separatorIndex));
                position.second = std::stoul(line.substr(separatorIndex + 1u));
            }
        }

        static size_t MeasureShortestPath(core::Grid<size_t> tileGrid)
        {
            std::set<Coordinates> exploredCoordinates;
            std::vector<Coordinates> coordinatesToExplore;
            coordinatesToExplore.reserve(_uniquePositionCount);
            coordinatesToExplore.push_back(_startPosition);

            tileGrid.WriteAt(_startPosition.first, _startPosition.second) = 0u;

            auto tryRegisterForExploration = [&](Coordinates&& newPosition, size_t const realCost)
            {
                if (exploredCoordinates.find(newPosition) != std::cend(exploredCoordinates))
                {
                    // Already explored, ignore it
                    return;
                }

                size_t& tileRealCost = tileGrid.WriteAt(newPosition.first, newPosition.second);
                if (tileRealCost > _uniquePositionCount)
                {
                    // Corrupted memory, a.k.a "walls", ignore it
                    return;
                }

                if (tileRealCost > realCost)
                {
                    tileRealCost = realCost;
                }

                if (std::find(std::cbegin(coordinatesToExplore), std::cend(coordinatesToExplore), newPosition) == std::cend(coordinatesToExplore))
                {
                    coordinatesToExplore.emplace_back(newPosition);
                }
            };

            while (!coordinatesToExplore.empty())
            {
                if (coordinatesToExplore.back() == _endPosition)
                {
                    // We've reached the end!
                    break;
                }

                Coordinates const currentPosition = coordinatesToExplore.back();
                exploredCoordinates.emplace(std::move(coordinatesToExplore.back()));
                coordinatesToExplore.pop_back();

                size_t const realCost = tileGrid.ReadAt(currentPosition.first, currentPosition.second);
                size_t const nextRealCost = realCost + 1u;

                if (currentPosition.first > 0u)
                {
                    tryRegisterForExploration({ currentPosition.first - 1u, currentPosition.second }, nextRealCost);
                }

                if (currentPosition.second > 0u)
                {
                    tryRegisterForExploration({ currentPosition.first, currentPosition.second - 1u }, nextRealCost);
                }

                if (currentPosition.first < _gridSize - 1u)
                {
                    tryRegisterForExploration({ currentPosition.first + 1u, currentPosition.second }, nextRealCost);
                }

                if (currentPosition.second < _gridSize - 1u)
                {
                    tryRegisterForExploration({ currentPosition.first, currentPosition.second + 1u }, nextRealCost);
                }

                std::sort(std::begin(coordinatesToExplore), std::end(coordinatesToExplore), [&](Coordinates const& lhs, Coordinates const& rhs)
                {
                    size_t const lhsTotalCost = tileGrid.ReadAt(lhs.first, lhs.second) + GetManhattanDistance(lhs, _endPosition);
                    size_t const rhsTotalCost = tileGrid.ReadAt(rhs.first, rhs.second) + GetManhattanDistance(rhs, _endPosition);
                    return lhsTotalCost > rhsTotalCost;
                });
            }

            return tileGrid.ReadAt(_endPosition.first, _endPosition.second);
        }

        static size_t GetManhattanDistance(Coordinates const& lhs, Coordinates const& rhs)
        {
            size_t const deltaFirst = rhs.first > lhs.first ? rhs.first - lhs.first : lhs.first - rhs.first;
            size_t const deltaSecond = rhs.second > lhs.second ? rhs.second - lhs.second : lhs.second - rhs.second;
            return deltaFirst + deltaSecond;
        }
    };
}

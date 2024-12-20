
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
        static Coordinates constexpr _startPosition = { 0u, 0u };
        static Coordinates constexpr _endPosition = { _gridSize - 1u, _gridSize - 1u };

    public:
        Challenge_2024_18(std::vector<std::string>&& inputLines)
            : Super(std::move(inputLines))
        {}

        void RunPartOne(std::ostream& outAnswer) override
        {
            std::vector<Coordinates> obstacles;
            ReadObstacles(obstacles);

            std::set<Coordinates> localObstacles;
            size_t const maxObstacleCount = obstacles.size() < 1024u ? obstacles.size() : 1024u;
            for (size_t obstacleIndex = 0u; obstacleIndex < maxObstacleCount; ++obstacleIndex)
            {
                localObstacles.emplace(obstacles[obstacleIndex]);
            }

            std::vector<Coordinates> path;
            if (!FindShortestPath(_startPosition, _endPosition, localObstacles, path))
            {
                outAnswer << "No path found";
                return;
            }

            outAnswer << path.size() - 1u;
        }

        void RunPartTwo(std::ostream& outAnswer) override
        {
            std::vector<Coordinates> obstacles;
            ReadObstacles(obstacles);

            std::set<Coordinates> localObstacles;
            std::vector<Coordinates> path;

            if (!FindShortestPath(_startPosition, _endPosition, localObstacles, path))
            {
                outAnswer << "No path found";
                return;
            }

            for (size_t obstacleIndex = 0u; obstacleIndex < obstacles.size(); ++obstacleIndex)
            {
                localObstacles.emplace(obstacles[obstacleIndex]);

                if (std::find(std::cbegin(path), std::cend(path), obstacles[obstacleIndex]) != std::cend(path))
                {
                    path.clear();
                    if (!FindAnyPath(_startPosition, _endPosition, localObstacles, path))
                    {
                        outAnswer << obstacles[obstacleIndex].first << ',' << obstacles[obstacleIndex].second;
                        return;
                    }
                }
            }

            outAnswer << "No path found";
        }

        void ReadObstacles(std::vector<Coordinates>& outObstacles) const
        {
            std::vector<std::string> const& lines = GetInputLines();
            outObstacles.resize(lines.size());

            for (size_t lineIndex = 0u; lineIndex < lines.size(); ++lineIndex)
            {
                std::string const& line = lines[lineIndex];
                size_t const separatorIndex = line.find(',');

                Coordinates& obstacle = outObstacles[lineIndex];
                obstacle.first = std::stoul(line.substr(0u, separatorIndex));
                obstacle.second = std::stoul(line.substr(separatorIndex + 1u));
            }
        }

        static bool FindShortestPath(Coordinates const& start, Coordinates const& end, std::set<Coordinates> const& obstacles, std::vector<Coordinates>& outPath)
        {
            outPath.clear();

            std::set<std::pair<Coordinates, Coordinates>> parentings;
            if (!FindShortestPath(start, end, obstacles, parentings))
            {
                return false;
            }

            outPath.reserve(parentings.size());
            outPath.emplace_back(end);

            while (outPath.back() != start)
            {
                Coordinates const& current = outPath.back();
                auto const it = std::find_if(std::cbegin(parentings), std::end(parentings), [&current](std::pair<Coordinates, Coordinates> const& parenting)
                {
                    return parenting.first == current;
                });

                if (it == std::cend(parentings))
                {
                    outPath.clear();
                    return false;
                }

                outPath.push_back(it->second);
            }

            return true;
        }

        static bool FindShortestPath(Coordinates const& start, Coordinates const& end, std::set<Coordinates> const& obstacles, std::set<std::pair<Coordinates, Coordinates>>& outParentings)
        {
            using CoordinatesToExplore = std::tuple<Coordinates, Coordinates, size_t, size_t>;

            std::set<Coordinates> explored = obstacles;
            std::vector<CoordinatesToExplore> toExplore;
            toExplore.reserve(_gridSize * _gridSize * 4u);
            toExplore.emplace_back(start, start, 0u, GetManhattanDistance(start, end));

            while (!toExplore.empty())
            {
                Coordinates const current = std::get<0>(toExplore.back());
                if (explored.contains(current))
                {
                    toExplore.pop_back();
                    continue;
                }

                outParentings.emplace(current, std::get<1>(toExplore.back()));

                if (current == end)
                {
                    return true;
                }

                size_t const nextCost = std::get<2>(toExplore.back()) + 1u;
                explored.emplace(current);
                toExplore.pop_back();

                if (current.first > 0u)
                {
                    Coordinates const next = { current.first - 1u, current.second };
                    if (!explored.contains(next))
                    {
                        size_t const heuristicCost = GetManhattanDistance(next, current);
                        toExplore.emplace_back(next, current, nextCost, nextCost + heuristicCost);
                    }
                }

                if (current.second > 0u)
                {
                    Coordinates const next = { current.first, current.second - 1u };
                    if (!explored.contains(next))
                    {
                        size_t const heuristicCost = GetManhattanDistance(next, current);
                        toExplore.emplace_back(next, current, nextCost, nextCost + heuristicCost);
                    }
                }

                if (current.first < _gridSize - 1u)
                {
                    Coordinates const next = { current.first + 1u, current.second };
                    if (!explored.contains(next))
                    {
                        size_t const heuristicCost = GetManhattanDistance(next, current);
                        toExplore.emplace_back(next, current, nextCost, nextCost + heuristicCost);
                    }
                }

                if (current.second < _gridSize - 1u)
                {
                    Coordinates const next = { current.first, current.second + 1u };
                    if (!explored.contains(next))
                    {
                        size_t const heuristicCost = GetManhattanDistance(next, current);
                        toExplore.emplace_back(next, current, nextCost, nextCost + heuristicCost);
                    }
                }

                std::sort(std::begin(toExplore), std::end(toExplore), [](CoordinatesToExplore const& lhs, CoordinatesToExplore const& rhs)
                {
                    return std::get<3>(lhs) > std::get<3>(rhs);
                });
            }

            return false;
        }

        static size_t GetManhattanDistance(Coordinates const& lhs, Coordinates const& rhs)
        {
            size_t const deltaFirst = lhs.first > rhs.first ? lhs.first - rhs.first : rhs.first - lhs.first;
            size_t const deltaSecond = lhs.second > rhs.second ? lhs.second - rhs.second : rhs.second - lhs.second;
            return deltaFirst + deltaSecond;
        }

        static bool FindAnyPath(Coordinates const& start, Coordinates const& end, std::set<Coordinates> const& obstacles, std::vector<Coordinates>& outPath)
        {
            std::set<Coordinates> explored;
            if (!FindAnyPath(start, end, obstacles, outPath, explored))
            {
                return false;
            }

            std::reverse(std::begin(outPath), std::end(outPath));
            return true;
        }

        static bool FindAnyPath(Coordinates const& current, Coordinates const& end, std::set<Coordinates> const& obstacles, std::vector<Coordinates>& outPath, std::set<Coordinates>& explored)
        {
            if (current == end)
            {
                outPath.push_back(current);
                return true;
            }

            if (obstacles.find(current) != std::cend(obstacles))
            {
                return false;
            }

            if (explored.find(current) != std::cend(explored))
            {
                return false;
            }

            explored.emplace(current);

            if (current.first < _gridSize - 1u)
            {
                Coordinates const next = { current.first + 1u, current.second };
                if (FindAnyPath(next, end, obstacles, outPath, explored))
                {
                    outPath.push_back(current);
                    return true;
                }
            }

            if (current.second < _gridSize - 1u)
            {
                Coordinates const next = { current.first, current.second + 1u };
                if (FindAnyPath(next, end, obstacles, outPath, explored))
                {
                    outPath.push_back(current);
                    return true;
                }
            }

            if (current.first > 0u)
            {
                Coordinates const next = { current.first - 1u, current.second };
                if (FindAnyPath(next, end, obstacles, outPath, explored))
                {
                    outPath.push_back(current);
                    return true;
                }
            }

            if (current.second > 0u)
            {
                Coordinates const next = { current.first, current.second - 1u};
                if (FindAnyPath(next, end, obstacles, outPath, explored))
                {
                    outPath.push_back(current);
                    return true;
                }
            }

            return false;
        }
    };
}

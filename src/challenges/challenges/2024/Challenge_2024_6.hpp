
#pragma once

#include "challenges/Challenge.hpp"

#include <array>

#include <core/containers/Grid.hpp>

namespace aoc::challenges
{
    class Challenge_2024_6 final : public Challenge<2024, 6>
    {
        using Super = Challenge<2024, 6>;

        static std::array<std::pair<int, int>, 4u> constexpr sm_directionOffsets = {{
            { -1, 0 },  // Up
            { 0, 1 },   // Right
            { 1, 0 },   // Down
            { 0, -1 }   // Left
        }};

        static std::array<char, 4u> constexpr sm_directionTokens = {{
            '^',    // Up
            '>',    // Right
            'v',    // Down
            '<'     // Left
        }};

        static char constexpr sm_obstacleToken = '#';
        static char constexpr sm_emptyToken = ' ';

    public:
        Challenge_2024_6(std::vector<std::string>&& inputLines)
            : Super(std::move(inputLines)) 
        {}

        void RunPartOne(std::ostream& outAnswer) override
        {
            core::Grid<char> room;
            std::pair<int, int> startingPosition;
            ParseInput(room, startingPosition);

            size_t distinctPositionCount = 0u;
            size_t facingDirectionIndex = 0u;
            std::pair<int, int> currentPosition = startingPosition;

            while (IsPositionInRoomBounds(room, currentPosition))
            {
                char const token = room.ReadAt(currentPosition.first, currentPosition.second);
                if (token == sm_obstacleToken)
                {
                    std::pair<int, int> const& facingDirectionOffset = sm_directionOffsets[facingDirectionIndex];
                    currentPosition.first -= facingDirectionOffset.first;
                    currentPosition.second -= facingDirectionOffset.second;
                    facingDirectionIndex = (facingDirectionIndex + 1u) % 4u;
                    continue;
                }

                if (token == sm_emptyToken)
                {
                    ++distinctPositionCount;
                    room.WriteAt(currentPosition.first, currentPosition.second) = sm_directionTokens[facingDirectionIndex];
                }

                std::pair<int, int> const& facingDirectionOffset = sm_directionOffsets[facingDirectionIndex];
                currentPosition.first += facingDirectionOffset.first;
                currentPosition.second += facingDirectionOffset.second;
            }

            outAnswer << distinctPositionCount;
        }

        void RunPartTwo(std::ostream& outAnswer) override
        {
            core::Grid<char> room;
            std::pair<int, int> startingPosition;
            ParseInput(room, startingPosition);

            size_t loopOptionCount = 0u;
            size_t facingDirectionIndex = 0u;
            std::pair<int, int> currentPosition = startingPosition;

            while (IsPositionInRoomBounds(room, currentPosition))
            {
                char const token = room.ReadAt(currentPosition.first, currentPosition.second);
                if (token == sm_obstacleToken)
                {
                    std::pair<int, int> const& facingDirectionOffset = sm_directionOffsets[facingDirectionIndex];
                    currentPosition.first -= facingDirectionOffset.first;
                    currentPosition.second -= facingDirectionOffset.second;
                    facingDirectionIndex = (facingDirectionIndex + 1u) % 4u;
                    continue;
                }

                if (token == sm_emptyToken)
                {
                    room.WriteAt(currentPosition.first, currentPosition.second) = sm_directionTokens[facingDirectionIndex];
                }

                if (SimulateNewObstacle(room, currentPosition, facingDirectionIndex))
                {
                    ++loopOptionCount;
                }

                std::pair<int, int> const& facingDirectionOffset = sm_directionOffsets[facingDirectionIndex];
                currentPosition.first += facingDirectionOffset.first;
                currentPosition.second += facingDirectionOffset.second;
            }

            outAnswer << loopOptionCount;
        }

        void ParseInput(core::Grid<char>& outRoom, std::pair<int, int>& outStartingPosition) const
        {
            std::vector<std::string> const& lines = GetInputLines();
            outRoom.Resize(lines.size(), lines[0].size());
            outRoom.ForEach([&lines, &outStartingPosition](char& item, size_t const lineIndex, size_t const columnIndex) {
                char const token = lines[lineIndex][columnIndex];
                if (token == sm_obstacleToken)
                {
                    item = sm_obstacleToken;
                }
                else
                {
                    if (token == sm_directionTokens[0])
                    {
                        outStartingPosition = { static_cast<int>(lineIndex), static_cast<int>(columnIndex) };
                    }

                    item = sm_emptyToken;
                }
            });
        }

        static bool IsPositionInRoomBounds(core::Grid<char> const& room, std::pair<int, int> const& position)
        {
            return position.first >= 0 &&
                position.first < static_cast<int>(room.GetLineCount()) &&
                position.second >= 0 &&
                position.second < static_cast<int>(room.GetColumnCount());
        }

        static bool SimulateNewObstacle(core::Grid<char> const& initialRoom, std::pair<int, int> currentPosition, size_t facingDirectionIndex)
        {
            std::pair<int, int> const newObstaclePosition = {
                currentPosition.first + sm_directionOffsets[facingDirectionIndex].first,
                currentPosition.second + sm_directionOffsets[facingDirectionIndex].second
            };

            if (!IsPositionInRoomBounds(initialRoom, newObstaclePosition))
            {
                // Would be placing an obstacle out of bounds
                return false;
            }

            if (initialRoom.ReadAt(newObstaclePosition.first, newObstaclePosition.second) != sm_emptyToken)
            {
                // This means there is either already an obstacle there, or we're creating a paradox as we've already moved here
                return false;
            }

            core::Grid<char> room = initialRoom;
            room.WriteAt(newObstaclePosition.first, newObstaclePosition.second) = sm_obstacleToken;

            facingDirectionIndex = (facingDirectionIndex + 1u) % 4u;

            while (IsPositionInRoomBounds(room, currentPosition))
            {
                char const token = room.ReadAt(currentPosition.first, currentPosition.second);
                if (token == sm_directionTokens[facingDirectionIndex])
                {
                    // We reached an already explored path! Therefore loop!
                    return true;
                }

                if (token == sm_obstacleToken)
                {
                    std::pair<int, int> const& facingDirectionOffset = sm_directionOffsets[facingDirectionIndex];
                    currentPosition.first -= facingDirectionOffset.first;
                    currentPosition.second -= facingDirectionOffset.second;
                    facingDirectionIndex = (facingDirectionIndex + 1u) % 4u;
                    continue;
                }

                if (token == sm_emptyToken)
                {
                    room.WriteAt(currentPosition.first, currentPosition.second) = sm_directionTokens[facingDirectionIndex];
                }

                std::pair<int, int> const& facingDirectionOffset = sm_directionOffsets[facingDirectionIndex];
                currentPosition.first += facingDirectionOffset.first;
                currentPosition.second += facingDirectionOffset.second;
            }

            return false;
        }
    };
}

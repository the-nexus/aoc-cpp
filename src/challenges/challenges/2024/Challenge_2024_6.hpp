
#pragma once

#include "challenges/Challenge.hpp"

#include <array>

#include <core/containers/Grid.hpp>

namespace aoc::challenges
{
    class Challenge_2024_6 final : public Challenge<2024, 6>
    {
        using Super = Challenge<2024, 6>;

        static std::array<std::pair<int, int>, 4u> constexpr _directionOffsets = {{
            { -1, 0 },  // Up
            { 0, 1 },   // Right
            { 1, 0 },   // Down
            { 0, -1 }   // Left
        }};

        static std::array<char, 4u> constexpr _directionTokens = {{
            '^',    // Up
            '>',    // Right
            'v',    // Down
            '<'     // Left
        }};

        static char constexpr _obstacleToken = '#';
        static char constexpr _emptyToken = ' ';

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
                if (token == _obstacleToken)
                {
                    std::pair<int, int> const& facingDirectionOffset = _directionOffsets[facingDirectionIndex];
                    currentPosition.first -= facingDirectionOffset.first;
                    currentPosition.second -= facingDirectionOffset.second;
                    facingDirectionIndex = (facingDirectionIndex + 1u) % 4u;
                    continue;
                }

                if (token == _emptyToken)
                {
                    ++distinctPositionCount;
                    room.WriteAt(currentPosition.first, currentPosition.second) = _directionTokens[facingDirectionIndex];
                }

                std::pair<int, int> const& facingDirectionOffset = _directionOffsets[facingDirectionIndex];
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
                if (token == _obstacleToken)
                {
                    std::pair<int, int> const& facingDirectionOffset = _directionOffsets[facingDirectionIndex];
                    currentPosition.first -= facingDirectionOffset.first;
                    currentPosition.second -= facingDirectionOffset.second;
                    facingDirectionIndex = (facingDirectionIndex + 1u) % 4u;
                    continue;
                }

                if (token == _emptyToken)
                {
                    room.WriteAt(currentPosition.first, currentPosition.second) = _directionTokens[facingDirectionIndex];
                }

                if (CanPathMerge(room, currentPosition, (facingDirectionIndex + 1u) % 4u))
                {
                    std::cout << currentPosition.first + _directionOffsets[facingDirectionIndex].first << ", "<< currentPosition.second + _directionOffsets[facingDirectionIndex].second << "\n";
                    ++loopOptionCount;
                }

                std::pair<int, int> const& facingDirectionOffset = _directionOffsets[facingDirectionIndex];
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
                if (token == _obstacleToken)
                {
                    item = _obstacleToken;
                }
                else
                {
                    if (token == _directionTokens[0])
                    {
                        outStartingPosition = { static_cast<int>(lineIndex), static_cast<int>(columnIndex) };
                    }

                    item = _emptyToken;
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

        static bool CanPathMerge(core::Grid<char> const& room, std::pair<int, int> position, size_t const directionIndex)
        {
            std::pair<int, int> const& directionOffset = _directionOffsets[directionIndex];
            char const directionToken = _directionTokens[directionIndex];

            while (IsPositionInRoomBounds(room, position))
            {
                char const token = room.ReadAt(position.first, position.second);
                if (token == _obstacleToken)
                {
                    break;
                }

                if (token == directionToken)
                {
                    return true;
                }

                position.first += directionOffset.first;
                position.second += directionOffset.second;
            }

            return false;
        }
    };
}

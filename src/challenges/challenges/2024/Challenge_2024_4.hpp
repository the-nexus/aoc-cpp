
#pragma once

#include "challenges/Challenge.hpp"

#include <array>

#include <core/containers/Grid.hpp>

namespace aoc::challenges
{
    class Challenge_2024_4 final : public Challenge<2024, 4>
    {
        using Super = Challenge<2024, 4>;

    public:
        Challenge_2024_4(std::vector<std::string>&& inputLines)
            : Super(std::move(inputLines)) 
        {}

        void RunPartOne(std::ostream& outAnswer) override
        {
            size_t constexpr padding = 3u;
            size_t const lineCount = GetInputLines().size();
            size_t const columnCount = GetInputLine(0).size();

            core::Grid<char> crossword = { lineCount + 2u * padding, columnCount + 2u * padding };
            crossword.SetAll('.');

            for (size_t lineIndex = 0u; lineIndex < lineCount; ++lineIndex)
            {
                for (size_t columnIndex = 0u; columnIndex < columnCount; ++columnIndex)
                {
                    crossword.WriteAt(lineIndex + padding, columnIndex + padding) = GetInputLines()[lineIndex][columnIndex];
                }
            }

            size_t occurenceCount = 0u;
            for (size_t lineIndex = padding; lineIndex < crossword.GetLineCount() - padding; ++lineIndex)
            {
                for (size_t columnIndex = padding; columnIndex < crossword.GetColumnCount() - padding; ++columnIndex)
                {
                    occurenceCount += CountAllXMAS(crossword, lineIndex, columnIndex);
                }
            }

            outAnswer << occurenceCount;
        }

        void RunPartTwo(std::ostream& outAnswer) override 
        {
            Super::RunPartTwo(outAnswer);
        }

        size_t CountAllXMAS(core::Grid<char> const& crossword, size_t const lineIndex, size_t const columnIndex) const
        {
            if (crossword.ReadAt(lineIndex, columnIndex) != 'X')
            {
                return 0u;
            }

            size_t count = 0u;

            // Up
            if (crossword.ReadAt(lineIndex - 1u, columnIndex) == 'M' &&
                crossword.ReadAt(lineIndex - 2u, columnIndex) == 'A'&&
                crossword.ReadAt(lineIndex - 3u, columnIndex) == 'S')
            {
                ++count;
            }

            // Down
            if (crossword.ReadAt(lineIndex + 1u, columnIndex) == 'M' &&
                crossword.ReadAt(lineIndex + 2u, columnIndex) == 'A'&&
                crossword.ReadAt(lineIndex + 3u, columnIndex) == 'S')
            {
                ++count;
            }

            // Left
            if (crossword.ReadAt(lineIndex, columnIndex - 1u) == 'M' &&
                crossword.ReadAt(lineIndex, columnIndex - 2u) == 'A'&&
                crossword.ReadAt(lineIndex, columnIndex - 3u) == 'S')
            {
                ++count;
            }

            // Right
            if (crossword.ReadAt(lineIndex, columnIndex + 1u) == 'M' &&
                crossword.ReadAt(lineIndex, columnIndex + 2u) == 'A'&&
                crossword.ReadAt(lineIndex, columnIndex + 3u) == 'S')
            {
                ++count;
            }

            // Diagonal Up-Left
            if (crossword.ReadAt(lineIndex - 1u, columnIndex - 1u) == 'M' &&
                crossword.ReadAt(lineIndex - 2u, columnIndex - 2u) == 'A'&&
                crossword.ReadAt(lineIndex - 3u, columnIndex - 3u) == 'S')
            {
                ++count;
            }

            // Diagonal Up-Right
            if (crossword.ReadAt(lineIndex - 1u, columnIndex + 1u) == 'M' &&
                crossword.ReadAt(lineIndex - 2u, columnIndex + 2u) == 'A'&&
                crossword.ReadAt(lineIndex - 3u, columnIndex + 3u) == 'S')
            {
                ++count;
            }

            // Diagonal Down-Left
            if (crossword.ReadAt(lineIndex + 1u, columnIndex - 1u) == 'M' &&
                crossword.ReadAt(lineIndex + 2u, columnIndex - 2u) == 'A'&&
                crossword.ReadAt(lineIndex + 3u, columnIndex - 3u) == 'S')
            {
                ++count;
            }

            // Diagonal Down-Right
            if (crossword.ReadAt(lineIndex + 1u, columnIndex + 1u) == 'M' &&
                crossword.ReadAt(lineIndex + 2u, columnIndex + 2u) == 'A'&&
                crossword.ReadAt(lineIndex + 3u, columnIndex + 3u) == 'S')
            {
                ++count;
            }

            return count;
        }
    };
}

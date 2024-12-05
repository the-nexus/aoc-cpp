
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
            core::Grid<char> crossword;
            InitializeCrosswordGrid(crossword, padding);

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
            size_t constexpr padding = 3u;
            core::Grid<char> crossword;
            InitializeCrosswordGrid(crossword, padding);

            size_t occurenceCount = 0u;
            for (size_t lineIndex = padding; lineIndex < crossword.GetLineCount() - padding; ++lineIndex)
            {
                for (size_t columnIndex = padding; columnIndex < crossword.GetColumnCount() - padding; ++columnIndex)
                {
                    if (IsCrossMAS(crossword, lineIndex, columnIndex))
                    {
                        ++occurenceCount;
                    }
                }
            }

            outAnswer << occurenceCount;
        }

        void InitializeCrosswordGrid(core::Grid<char>& outCrossword, size_t const padding) const
        {
            std::vector<std::string> const& lines = GetInputLines();
            size_t const lineCount = lines.size();
            size_t const columnCount = lines[0].size();

            outCrossword = { lineCount + 2u * padding, columnCount + 2u * padding };
            outCrossword.SetAll('.');

            for (size_t lineIndex = 0u; lineIndex < lineCount; ++lineIndex)
            {
                std::string const& line = lines[lineIndex];
                for (size_t columnIndex = 0u; columnIndex < columnCount; ++columnIndex)
                {
                    outCrossword.WriteAt(lineIndex + padding, columnIndex + padding) = line[columnIndex];
                }
            }
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

        bool IsCrossMAS(core::Grid<char> const& crossword, size_t const lineIndex, size_t const columnIndex)
        {
            if (crossword.ReadAt(lineIndex, columnIndex) != 'A')
            {
                return false;
            }

            // First diagonal
            bool isFirstDiagonalMAS = crossword.ReadAt(lineIndex - 1u, columnIndex - 1u) == 'M' && crossword.ReadAt(lineIndex + 1u, columnIndex + 1u) == 'S';
            bool isFirstDiagonalSAM = crossword.ReadAt(lineIndex - 1u, columnIndex - 1u) == 'S' && crossword.ReadAt(lineIndex + 1u, columnIndex + 1u) == 'M';
            if (!isFirstDiagonalMAS && !isFirstDiagonalSAM)
            {
                return false;
            }

            // Second diagonal
            bool isSecondDiagonalMAS = crossword.ReadAt(lineIndex - 1u, columnIndex + 1u) == 'M' && crossword.ReadAt(lineIndex + 1u, columnIndex - 1u) == 'S';
            bool isSecondDiagonalSAM = crossword.ReadAt(lineIndex - 1u, columnIndex + 1u) == 'S' && crossword.ReadAt(lineIndex + 1u, columnIndex - 1u) == 'M';
            if (!isSecondDiagonalMAS && !isSecondDiagonalSAM)
            {
                return false;
            }

            return true;
        }
    };
}

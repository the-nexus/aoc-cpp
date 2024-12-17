
#pragma once

#include "challenges/Challenge.hpp"

#include <map>
#include <set>

namespace aoc::challenges
{
    class Challenge_2024_8 final : public Challenge<2024, 8>
    {
        using Super = Challenge<2024, 8>;
        using Coordinates = std::pair<int, int>;

    public:
        Challenge_2024_8(std::vector<std::string>&& inputLines)
            : Super(std::move(inputLines))
        {}

        void RunPartOne(std::ostream& outAnswer) override
        {
            std::map<char, std::vector<Coordinates>> antennas;
            AssembleAntennas(antennas);

            std::set<Coordinates> antinodes;
            ComputeAntinodes(antennas, false, antinodes);

            outAnswer << antinodes.size();
        }

        void RunPartTwo(std::ostream& outAnswer) override
        {
            std::map<char, std::vector<Coordinates>> antennas;
            AssembleAntennas(antennas);

            std::set<Coordinates> antinodes;
            ComputeAntinodes(antennas, true, antinodes);

            outAnswer << antinodes.size();
        }

        void AssembleAntennas(std::map<char, std::vector<Coordinates>>& outAntennas) const
        {
            std::vector<std::string> const& lines = GetInputLines();
            for (size_t lineIndex = 0u; lineIndex < lines.size(); ++lineIndex)
            {
                std::string const& line = lines[lineIndex];
                for (size_t columnIndex = 0u; columnIndex < line.size(); ++columnIndex)
                {
                    if (line[columnIndex] != '.')
                    {
                        auto it = outAntennas.try_emplace(line[columnIndex]).first;
                        it->second.emplace_back(lineIndex, columnIndex);
                    }
                }
            }
        }

        void ComputeAntinodes(std::map<char, std::vector<Coordinates>> const& antennas, bool const useUpdatedModel, std::set<Coordinates>& outAntinodes) const
        {
            for (std::pair<char, std::vector<Coordinates>> const& antennaGroup : antennas)
            {
                ComputeAntinodes(antennaGroup.second, useUpdatedModel, outAntinodes);
            }
        }

        void ComputeAntinodes(std::vector<Coordinates> const& coordinates, bool const useUpdatedModel, std::set<Coordinates>& outAntinodes) const
        {
            for (size_t firstIndex = 0u; firstIndex < coordinates.size(); ++firstIndex)
            {
                Coordinates const& firstCoordinates = coordinates[firstIndex];
                for (size_t secondIndex = firstIndex + 1u; secondIndex < coordinates.size(); ++secondIndex)
                {
                    Coordinates const& secondCoordinates = coordinates[secondIndex];
                    int const deltaLine = secondCoordinates.first - firstCoordinates.first;
                    int const deltaColumn = secondCoordinates.second - firstCoordinates.second;

                    ComputeAntinode(firstCoordinates, { -deltaLine, -deltaColumn }, useUpdatedModel, outAntinodes);
                    ComputeAntinode(secondCoordinates, { deltaLine, deltaColumn }, useUpdatedModel, outAntinodes);
                }
            }
        }

        void ComputeAntinode(Coordinates const& coordinates, Coordinates const& deltaCoordinates, bool const useUpdatedModel, std::set<Coordinates>& outAntinodes) const
        {
            if (useUpdatedModel && outAntinodes.find(coordinates) == std::cend(outAntinodes))
            {
                outAntinodes.insert(coordinates);
            }

            Coordinates antinode = coordinates;
            size_t const maxStepCount = useUpdatedModel ? GetInputLines().size() * GetInputLine(0).size() : 1u;
            size_t stepCount = 0u;

            while (stepCount++ < maxStepCount)
            {
                antinode.first += deltaCoordinates.first;
                antinode.second += deltaCoordinates.second;

                if (!AreCoordinatesWithinBounds(antinode))
                {
                    return;
                }

                if (outAntinodes.find(antinode) == std::cend(outAntinodes))
                {
                    outAntinodes.insert(antinode);
                }
            }
        }

        bool AreCoordinatesWithinBounds(Coordinates const& coordinates) const
        {
            int const lineCount = GetInputLines().size();
            int const columnCount = GetInputLine(0).size();
            return coordinates.first >= 0 && coordinates.first < lineCount
                && coordinates.second >= 0 && coordinates.second < columnCount;
        }
    };
}

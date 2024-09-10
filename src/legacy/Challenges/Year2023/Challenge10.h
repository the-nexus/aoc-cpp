
#pragma once

#include "Challenges/ChallengeAbstract.h"

namespace AOC::Challenges::Year2023
{
    class Challenge10 final : public ChallengeAbstract
    {
    private:
        enum PipeType : unsigned int
        {
            None                = 0,

            Connection_Up       = 1 << 1,
            Connection_Down     = 1 << 2,
            Connection_Left     = 1 << 3,
            Connection_Right    = 1 << 4,

            Pipe_LR             = Connection_Left   | Connection_Right,
            Pipe_UD             = Connection_Up     | Connection_Down,
            Pipe_UL             = Connection_Up     | Connection_Left,
            Pipe_UR             = Connection_Up     | Connection_Right,
            Pipe_DL             = Connection_Down   | Connection_Left,
            Pipe_DR             = Connection_Down   | Connection_Right,
            Pipe_Start          = Connection_Up     | Connection_Down   | Connection_Left   | Connection_Right
        };

        std::vector<std::vector<PipeType>> m_pipeGrid;
        size_t m_startLine = 0;
        size_t m_startColumn = 0;

    public:
        Challenge10(std::vector<std::string> const& inputLines)
        {
            m_pipeGrid.resize(inputLines.size());
            for (size_t line = 0; line < m_pipeGrid.size(); ++line)
            {
                m_pipeGrid[line].resize(inputLines[line].size());
                for (size_t column = 0; column < m_pipeGrid[line].size(); ++column)
                {
                    m_pipeGrid[line][column] = GetPipeTypeFromToken(inputLines[line][column]);
                    if (m_pipeGrid[line][column] == PipeType::Pipe_Start)
                    {
                        m_startLine = line;
                        m_startColumn = column;
                    }
                }
            }
        }

        virtual void Run_PartOne() override
        {
            std::vector<std::vector<bool>> visitedGrid;
            visitedGrid.resize(m_pipeGrid.size());
            for (size_t line = 0; line < visitedGrid.size(); ++line)
            {
                visitedGrid[line].resize(m_pipeGrid[line].size());
                for (size_t column = 0; column < visitedGrid[line].size(); ++column)
                {
                    visitedGrid[line][column] = 0;
                }
            }

            std::cout << GetFurthestDistance(m_startLine, m_startColumn, visitedGrid) << std::endl;
        }

        virtual void Run_PartTwo() override
        {
            std::cout << "WARNING: Part Two Not Implemented" << std::endl;
        }

    private:
        static PipeType GetPipeTypeFromToken(char const token)
        {
            switch (token)
            {
            case '-': return PipeType::Pipe_LR;
            case '|': return PipeType::Pipe_UD;
            case 'J': return PipeType::Pipe_UL;
            case 'L': return PipeType::Pipe_UR;
            case '7': return PipeType::Pipe_DL;
            case 'F': return PipeType::Pipe_DR;
            case 'S': return PipeType::Pipe_Start;
            default: return PipeType::None;
            }
        }

        size_t GetFurthestDistance(size_t const line, size_t const column, std::vector<std::vector<bool>>& visitedGrid) const
        {
            visitedGrid[line][column] = true;
            size_t furthestDistance = 0;

            // Up
            if (line > 0 &&
                !visitedGrid[line - 1][column] &&
                (m_pipeGrid[line][column] & PipeType::Connection_Up) > 0 &&
                (m_pipeGrid[line - 1][column] & PipeType::Connection_Down) > 0)
            {
                size_t const distance = GetFurthestDistance(line - 1, column, visitedGrid) + 1;
                if (distance > furthestDistance) furthestDistance = distance;
            }

            // Down
            if (line < m_pipeGrid.size() - 1 &&
                !visitedGrid[line + 1][column] &&
                (m_pipeGrid[line][column] & PipeType::Connection_Down) > 0 &&
                (m_pipeGrid[line + 1][column] & PipeType::Connection_Up) > 0)
            {
                size_t const distance = GetFurthestDistance(line + 1, column, visitedGrid) + 1;
                if (distance > furthestDistance) furthestDistance = distance;
            }

            // Left
            if (column > 0 &&
                !visitedGrid[line][column - 1] &&
                (m_pipeGrid[line][column] & PipeType::Connection_Left) > 0 &&
                (m_pipeGrid[line][column - 1] & PipeType::Connection_Right) > 0)
            {
                size_t const distance = GetFurthestDistance(line, column - 1, visitedGrid) + 1;
                if (distance > furthestDistance) furthestDistance = distance;
            }

            // Right
            if (column < m_pipeGrid[0].size() - 1 &&
                !visitedGrid[line][column + 1] &&
                (m_pipeGrid[line][column] & PipeType::Connection_Right) > 0 &&
                (m_pipeGrid[line][column + 1] & PipeType::Connection_Left) > 0)
            {
                size_t const distance = GetFurthestDistance(line, column + 1, visitedGrid) + 1;
                if (distance > furthestDistance) furthestDistance = distance;
            }

            return furthestDistance;
        }
    };
}

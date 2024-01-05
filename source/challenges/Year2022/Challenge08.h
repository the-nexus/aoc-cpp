#pragma once

#include "../ChallengeAbstract.h"

namespace Year2022
{
    class Challenge08 final : public ChallengeAbstract
    {
    private:
        enum class EGridEdge
        {
            Up,
            Down,
            Left,
            Right
        };

        int** m_treeGrid = nullptr;
        int m_treeGridLineCount = 0;
        int m_treeGridColumnCount = 0;

    public:
        Challenge08(std::vector<std::string> const& inputLines)
        {
            m_treeGridLineCount = static_cast<int>(inputLines.size());
            m_treeGridColumnCount = static_cast<int>(inputLines[0].size());

            m_treeGrid = new int* [m_treeGridLineCount];
            for (int lineIndex = 0; lineIndex < m_treeGridLineCount; ++lineIndex)
            {
                m_treeGrid[lineIndex] = new int[m_treeGridColumnCount];
                for (int columnIndex = 0; columnIndex < m_treeGridColumnCount; ++columnIndex)
                {
                    m_treeGrid[lineIndex][columnIndex] = static_cast<int>(inputLines[lineIndex][columnIndex] - '0');
                }
            }
        }

        ~Challenge08()
        {
            for (int gridLine = 0; gridLine < m_treeGridLineCount; ++gridLine)
            {
                delete m_treeGrid[gridLine];
            }
            delete m_treeGrid;
        }

        virtual void Run_PartOne() override
        {
            int visibleTreeCount = 0;
            for (int lineIndex = 0; lineIndex < m_treeGridLineCount; ++lineIndex)
            {
                if (lineIndex == 0 || lineIndex == m_treeGridLineCount - 1)
                {
                    visibleTreeCount += m_treeGridColumnCount;
                }
                else
                {
                    for (int columnIndex = 0; columnIndex < m_treeGridColumnCount; ++columnIndex)
                    {
                        if (columnIndex == 0 || columnIndex == m_treeGridColumnCount - 1)
                        {
                            ++visibleTreeCount;
                        }
                        else if (IsTreeVisibleFromGridEdge(lineIndex, columnIndex, EGridEdge::Up) ||
                            IsTreeVisibleFromGridEdge(lineIndex, columnIndex, EGridEdge::Down) ||
                            IsTreeVisibleFromGridEdge(lineIndex, columnIndex, EGridEdge::Left) ||
                            IsTreeVisibleFromGridEdge(lineIndex, columnIndex, EGridEdge::Right))
                        {
                            ++visibleTreeCount;
                        }
                    }
                }
            }

            std::cout << visibleTreeCount << std::endl;
        }

        virtual void Run_PartTwo() override
        {
            int bestScore = 0;
            for (int lineIndex = 0; lineIndex < m_treeGridLineCount; ++lineIndex)
            {
                for (int columnIndex = 0; columnIndex < m_treeGridColumnCount; ++columnIndex)
                {
                    int const score = GetTreeScoreTowardsEdge(lineIndex, columnIndex, EGridEdge::Up) *
                        GetTreeScoreTowardsEdge(lineIndex, columnIndex, EGridEdge::Down) *
                        GetTreeScoreTowardsEdge(lineIndex, columnIndex, EGridEdge::Left) *
                        GetTreeScoreTowardsEdge(lineIndex, columnIndex, EGridEdge::Right);

                    if (score > bestScore)
                    {
                        bestScore = score;
                    }
                }
            }

            std::cout << bestScore << std::endl;
        }

    private:
        bool IsTreeVisibleFromGridEdge(int const lineIndex, int const columnIndex, EGridEdge const gridEdge)
        {
            int const treeHeight = m_treeGrid[lineIndex][columnIndex];
            switch (gridEdge)
            {
            case EGridEdge::Up:
                for (int testLineIndex = lineIndex - 1; testLineIndex >= 0; --testLineIndex)
                {
                    if (m_treeGrid[testLineIndex][columnIndex] >= treeHeight)
                    {
                        return false;
                    }
                }
                break;

            case EGridEdge::Down:
                for (int testLineIndex = lineIndex + 1; testLineIndex < m_treeGridLineCount; ++testLineIndex)
                {
                    if (m_treeGrid[testLineIndex][columnIndex] >= treeHeight)
                    {
                        return false;
                    }
                }
                break;

            case EGridEdge::Left:
                for (int testColumnIndex = columnIndex - 1; testColumnIndex >= 0; --testColumnIndex)
                {
                    if (m_treeGrid[lineIndex][testColumnIndex] >= treeHeight)
                    {
                        return false;
                    }
                }
                break;

            case EGridEdge::Right:
                for (int testColumnIndex = columnIndex + 1; testColumnIndex < m_treeGridColumnCount; ++testColumnIndex)
                {
                    if (m_treeGrid[lineIndex][testColumnIndex] >= treeHeight)
                    {
                        return false;
                    }
                }
                break;
            }

            return true;
        }

        int GetTreeScoreTowardsEdge(int const lineIndex, int const columnIndex, EGridEdge const gridEdge)
        {
            int score = 0;
            int const treeHeight = m_treeGrid[lineIndex][columnIndex];
            switch (gridEdge)
            {
            case EGridEdge::Up:
                for (int testLineIndex = lineIndex - 1; testLineIndex >= 0; --testLineIndex)
                {
                    ++score;
                    if (m_treeGrid[testLineIndex][columnIndex] >= treeHeight)
                    {
                        break;
                    }
                }
                break;

            case EGridEdge::Down:
                for (int testLineIndex = lineIndex + 1; testLineIndex < m_treeGridLineCount; ++testLineIndex)
                {
                    ++score;
                    if (m_treeGrid[testLineIndex][columnIndex] >= treeHeight)
                    {
                        break;
                    }
                }
                break;

            case EGridEdge::Left:
                for (int testColumnIndex = columnIndex - 1; testColumnIndex >= 0; --testColumnIndex)
                {
                    ++score;
                    if (m_treeGrid[lineIndex][testColumnIndex] >= treeHeight)
                    {
                        break;
                    }
                }
                break;

            case EGridEdge::Right:
                for (int testColumnIndex = columnIndex + 1; testColumnIndex < m_treeGridColumnCount; ++testColumnIndex)
                {
                    ++score;
                    if (m_treeGrid[lineIndex][testColumnIndex] >= treeHeight)
                    {
                        break;
                    }
                }
                break;
            }

            return score;
        }
    };
}

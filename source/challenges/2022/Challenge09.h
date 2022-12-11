#pragma once

#include "../ChallengeAbstract.h"
#include "../tools/VectorTool.h"

namespace Year2022
{
    class Challenge09 : public ChallengeAbstract
    {
    public:
        std::vector<Vector2i> m_steps;

        virtual void SetUp(std::vector<std::string> const& inputLines) override
        {
            m_steps.reserve(inputLines.size() * 10);
            for (std::string const& line : inputLines)
            {
                Vector2i direction;
                switch (line[0])
                {
                case 'U': direction[1] = 1; break;
                case 'D': direction[1] = -1; break;
                case 'R': direction[0] = 1; break;
                case 'L': direction[0] = -1; break;
                default: break;
                }

                int const stepCount = atoi(line.substr(2).c_str());
                for (int stepIndex = 0; stepIndex < stepCount; ++stepIndex)
                {
                    m_steps.push_back(direction);
                }
            }
        }

        virtual void Run_PartOne() override
        {
            std::cout << SimulateRope(2) << std::endl;
        }

        virtual void Run_PartTwo() override
        {
            std::cout << SimulateRope(10) << std::endl;
        }

        virtual void CleanUp() override {}

    private:
        size_t SimulateRope(size_t const knotCount) const
        {
            std::vector<Vector2i> rope;
            rope.resize(knotCount);

            std::vector<Vector2i> uniqueTailPositions;
            uniqueTailPositions.reserve(m_steps.size());

            for (Vector2i const& step : m_steps)
            {
                rope[0] += step;
                for (size_t knotIndex = 1; knotIndex < knotCount; ++knotIndex)
                {
                    AdjustKnotPosition(rope[knotIndex - 1], rope[knotIndex]);
                }

                RegisterTailKnotPosition(rope.back(), uniqueTailPositions);
                //DrawRope<41>(rope);
            }

            return uniqueTailPositions.size();
        }

        void AdjustKnotPosition(Vector2i const& parentKnotPosition, Vector2i& knotPosition) const
        {
            Vector2i const knotOffset = parentKnotPosition - knotPosition;
            if (knotOffset[0] > 1) // Parent moved up
            {
                knotPosition[0] = parentKnotPosition[0] - 1;
                knotPosition[1] = parentKnotPosition[1];
            }
            else if (knotOffset[0] < -1) // Parent moved down
            {
                knotPosition[0] = parentKnotPosition[0] + 1;
                knotPosition[1] = parentKnotPosition[1];
            }
            else if (knotOffset[1] > 1) // Parent moved right
            {
                knotPosition[0] = parentKnotPosition[0];
                knotPosition[1] = parentKnotPosition[1] - 1;
            }
            else if (knotOffset[1] < -1) // Parent moved left
            {
                knotPosition[0] = parentKnotPosition[0];
                knotPosition[1] = parentKnotPosition[1] + 1;
            }
        }

        void RegisterTailKnotPosition(Vector2i const& tailKnotPosition, std::vector<Vector2i>& uniqueTailPositions) const
        {
            if (std::find(uniqueTailPositions.begin(), uniqueTailPositions.end(), tailKnotPosition) == uniqueTailPositions.end())
            {
                uniqueTailPositions.push_back(tailKnotPosition);
            }
        }

        template <int GRID_SIZE>
        void DrawRope(std::vector<Vector2i> const& rope) const
        {
            Vector2i const anchor(GRID_SIZE / 2 - 1);

            char grid[GRID_SIZE][GRID_SIZE];
            for (int j = 0; j < GRID_SIZE; ++j)
            {
                for (int i = 0; i < GRID_SIZE; ++i)
                {
                    grid[j][i] = '.';
                }
            }

            // Place the knot symbols
            Vector2i invertedKnot = Vector2i(rope[0][0], -rope[0][1]);
            Vector2i knotPos = anchor + invertedKnot;
            grid[knotPos[1]][knotPos[0]] = 'H';

            for (size_t knotIndex = 1; knotIndex < rope.size(); ++knotIndex)
            {
                invertedKnot = Vector2i(rope[knotIndex][0], -rope[knotIndex][1]);
                knotPos = anchor + invertedKnot;
                if (grid[knotPos[1]][knotPos[0]] == '.')
                {
                    grid[knotPos[1]][knotPos[0]] = '0' + static_cast<char>(knotIndex);
                }
            }

            // Place the start symbol
            if (grid[anchor[1]][anchor[0]] == '.')
            {
                grid[anchor[1]][anchor[0]] = 'S';
            }

            // Draw the grid
            for (int j = 0; j < GRID_SIZE; ++j)
            {
                for (int i = 0; i < GRID_SIZE; ++i)
                {
                    std::cout << grid[j][i];
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }
    };
}

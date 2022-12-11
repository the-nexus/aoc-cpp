#pragma once

#include "../ChallengeAbstract.h"
#include "../tools/VectorTool.h"

namespace Year2022
{
    class Challenge09 : public ChallengeAbstract
    {
    public:
        enum class EStepDirection
        {
            Up,
            Down,
            Left,
            Right
        };

        std::vector<std::pair<EStepDirection, int>> m_ropeHeadInstructions;

        virtual void SetUp(std::vector<std::string> const& inputLines) override
        {
            m_ropeHeadInstructions.resize(inputLines.size());
            for (size_t lineIndex = 0; lineIndex < inputLines.size(); ++lineIndex)
            {
                std::string const& inputString = inputLines[lineIndex];
                m_ropeHeadInstructions[lineIndex].second = atoi(inputLines[lineIndex].substr(2).c_str());

                switch (inputLines[lineIndex][0])
                {
                case 'U': m_ropeHeadInstructions[lineIndex].first = EStepDirection::Up; break;
                case 'D': m_ropeHeadInstructions[lineIndex].first = EStepDirection::Down; break;
                case 'L': m_ropeHeadInstructions[lineIndex].first = EStepDirection::Left; break;
                case 'R': m_ropeHeadInstructions[lineIndex].first = EStepDirection::Right; break;
                default: break;
                }
            }
        }

        virtual void Run_PartOne() override
        {
            size_t constexpr knotCount = 2;
            Vector2i rope[knotCount];

            std::vector<Vector2i> visitedTailPositions;
            visitedTailPositions.reserve(m_ropeHeadInstructions.size());
            visitedTailPositions.push_back(rope[knotCount - 1]);

            for (std::pair<EStepDirection, int> const& instruction : m_ropeHeadInstructions)
            {
                for (int distanceMoved = 0; distanceMoved < instruction.second; ++distanceMoved)
                {
                    // Move the head knot by 1 step according to the instructions
                    switch (instruction.first)
                    {
                    case EStepDirection::Up: rope[0][1] += 1; break;
                    case EStepDirection::Down: rope[0][1] -= 1; break;
                    case EStepDirection::Left: rope[0][0] -= 1; break;
                    case EStepDirection::Right: rope[0][0] += 1; break;
                    }

                    if (TryMoveKnot(rope[0], rope[1]))
                    {
                        if (std::find(visitedTailPositions.begin(), visitedTailPositions.end(), rope[1]) == visitedTailPositions.end())
                        {
                            visitedTailPositions.push_back(rope[1]); // Remember unique positions visited by the tail of the rope
                        }
                    }

                    // Move all the other knots
                    //for (size_t knotIndex = 1; knotIndex < knotCount; ++knotIndex)
                    //{
                    //    if (TryMoveKnot(rope[knotIndex - 1], rope[knotIndex]) && knotIndex == knotCount - 1)
                    //    {
                    //        if (std::find(visitedTailPositions.begin(), visitedTailPositions.end(), rope[knotIndex]) == visitedTailPositions.end())
                    //        {
                    //            visitedTailPositions.push_back(rope[knotIndex]); // Remember unique positions visited by the tail of the rope
                    //        }
                    //    }
                    //}
                }
            }

            std::cout << visitedTailPositions.size() << std::endl;
        }

        virtual void Run_PartTwo() override
        {
            std::cout << "WARNING: Part Two Not Implemented" << std::endl;
        }

        virtual void CleanUp() override {}

    private:
        bool TryMoveKnot(Vector2i const& parentKnotPosition, Vector2i& knotPosition) const
        {
            Vector2i const knotOffset = parentKnotPosition - knotPosition;
            if (knotOffset[0] > 1)
            {
                knotPosition[0] = parentKnotPosition[0] - 1;
                knotPosition[1] = parentKnotPosition[1];
                return true; // Has moved right
            }
            else if (knotOffset[0] < -1)
            {
                knotPosition[0] = parentKnotPosition[0] + 1;
                knotPosition[1] = parentKnotPosition[1];
                return true; // Has moved left
            }
            else if (knotOffset[1] > 1)
            {
                knotPosition[0] = parentKnotPosition[0];
                knotPosition[1] = parentKnotPosition[1] - 1;
                return true; // Has moved up
            }
            else if (knotOffset[1] < -1)
            {
                knotPosition[0] = parentKnotPosition[0];
                knotPosition[1] = parentKnotPosition[1] - 1;
                return true; // Has moved
            }

            return false; // Has not moved
        }
    };
}

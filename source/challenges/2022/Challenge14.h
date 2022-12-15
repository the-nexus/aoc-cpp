#pragma once

#include "../ChallengeAbstract.h"
#include "../tools/StringTool.h"
#include "../tools/VectorTool.h"
#include <set>

namespace Year2022
{
    class Challenge14 : public ChallengeAbstract
    {
    private:
        std::set<Vector2i> m_colliders;
        Vector2i m_emitterPos = Vector2i(500, 0);
        int m_infiniteFloorHeight = 0;

    public:
        virtual void SetUp(std::vector<std::string> const& inputLines) override
        {
            std::vector<std::string> args;
            for (std::string const& inputLine : inputLines)
            {
                args.clear();
                StringTool::SplitString(inputLine, " -> ", args);

                Vector2i lastPoint;
                for (size_t argIndex = 0; argIndex < args.size(); ++argIndex)
                {
                    size_t const separatorIndex = args[argIndex].find_first_of(',');

                    Vector2i nextPoint(
                        atoi(args[argIndex].substr(0, separatorIndex).c_str()),
                        atoi(args[argIndex].substr(separatorIndex + 1).c_str())
                    );

                    if (argIndex > 0)
                    {
                        AddLineAsPoints(lastPoint, nextPoint, m_colliders);
                    }

                    if (nextPoint[1] > m_infiniteFloorHeight)
                    {
                        m_infiniteFloorHeight = nextPoint[1] + 2;
                    }

                    lastPoint = nextPoint;
                }
            }
        }

        virtual void Run_PartOne() override
        {
            std::set<Vector2i> sandUnits;
            Vector2i sandPos = m_emitterPos;
            while (sandPos[1] < m_infiniteFloorHeight)
            {
                StepSandUnit(sandPos, sandUnits, false);
            }

            std::cout << sandUnits.size() << std::endl;
        }

        virtual void Run_PartTwo() override
        {
            std::set<Vector2i> sandUnits;
            Vector2i sandPos = m_emitterPos;
            while (sandUnits.find(m_emitterPos) == sandUnits.end())
            {
                StepSandUnit(sandPos, sandUnits, true);
            }

            std::cout << sandUnits.size() << std::endl;
        }

        virtual void CleanUp() override {}

    private:
        void AddLineAsPoints(Vector2i const& lineStart, Vector2i const& lineEnd, std::set<Vector2i>& uniquePoints)
        {
            bool const isHorizontalLine = lineStart[1] == lineEnd[1];

            Vector2i point;
            int& variablePos = isHorizontalLine ? point[0] : point[1];
            int variablePosStart, variablePosEnd;

            if (isHorizontalLine)
            {
                point[1] = lineStart[1];
                if (lineStart[0] < lineEnd[0])
                {
                    variablePosStart = lineStart[0];
                    variablePosEnd = lineEnd[0];
                }
                else
                {
                    variablePosStart = lineEnd[0];
                    variablePosEnd = lineStart[0];
                }
            }
            else
            {
                point[0] = lineStart[0];
                if (lineStart[1] < lineEnd[1])
                {
                    variablePosStart = lineStart[1];
                    variablePosEnd = lineEnd[1];
                }
                else
                {
                    variablePosStart = lineEnd[1];
                    variablePosEnd = lineStart[1];
                }
            }

            for (variablePos = variablePosStart; variablePos <= variablePosEnd; ++variablePos)
            {
                if (uniquePoints.find(point) == uniquePoints.end())
                {
                    uniquePoints.insert(point);
                }
            }
        }

        void StepSandUnit(Vector2i& sandPos, std::set<Vector2i>& sandUnits, bool const isInfiniteFloorCollider)
        {
            sandPos[1] += 1; // Check down
            if (isInfiniteFloorCollider && sandPos[1] >= m_infiniteFloorHeight)
            {
                sandPos[1] -= 1; // Reset to starting pos

                sandUnits.insert(sandPos); // Store it as a "collider" with the rest of settled sand
                sandPos = m_emitterPos; // Restart with a new sand unit
            }
            else if (sandUnits.find(sandPos) != sandUnits.end() || m_colliders.find(sandPos) != m_colliders.end())
            {
                sandPos[0] -= 1; // Check down-left
                if (sandUnits.find(sandPos) != sandUnits.end() || m_colliders.find(sandPos) != m_colliders.end())
                {
                    sandPos[0] += 2; // Check down-right
                    if (sandUnits.find(sandPos) != sandUnits.end() || m_colliders.find(sandPos) != m_colliders.end())
                    {
                        sandPos -= 1; // Reset to starting pos

                        sandUnits.insert(sandPos); // Store it as a "collider" with the rest of settled sand
                        sandPos = m_emitterPos; // Restart with a new sand unit
                    }
                }
            }
        }
    };
}

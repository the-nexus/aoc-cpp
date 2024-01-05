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
            }

            return uniqueTailPositions.size();
        }

        void AdjustKnotPosition(Vector2i const& parentKnotPosition, Vector2i& knotPosition) const
        {
            Vector2f const knotOffset(
                static_cast<float>(parentKnotPosition[0] - knotPosition[0]),
                static_cast<float>(parentKnotPosition[1] - knotPosition[1])
            );

            float const knotMagnitude = Vector2f::Magnitude(knotOffset);
            if (knotMagnitude > 1.f)
            {
                Vector2i const knotAdjustment(
                    static_cast<int>(round(knotOffset[0] / knotMagnitude)),
                    static_cast<int>(round(knotOffset[1] / knotMagnitude))
                );

                knotPosition = parentKnotPosition - knotAdjustment;
            }
        }

        void RegisterTailKnotPosition(Vector2i const& tailKnotPosition, std::vector<Vector2i>& uniqueTailPositions) const
        {
            if (std::find(uniqueTailPositions.begin(), uniqueTailPositions.end(), tailKnotPosition) == uniqueTailPositions.end())
            {
                uniqueTailPositions.push_back(tailKnotPosition);
            }
        }
    };
}

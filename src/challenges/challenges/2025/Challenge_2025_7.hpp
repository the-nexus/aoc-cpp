
#pragma once

#include "challenges/Challenge.hpp"

namespace aoc::challenges
{
    class Challenge_2025_7 final : public Challenge<2025, 7>
    {
        using Super = Challenge<2025, 7>;

    public:
        Challenge_2025_7(std::vector<std::string>&& inputLines)
            : Super(std::move(inputLines))
        {}

        void RunPartOne(std::ostream& outAnswer) override
        {
            const std::vector<std::string>& lines = GetInputLines();

            std::vector<bool> state;
            state.resize(lines.front().size(), false);
            state[lines.front().find('S')] = true;

            size_t splitCount = 0;
            for (auto lineIt = std::cbegin(lines) + 1; lineIt != std::cend(lines); ++lineIt)
            {
                const std::string& line = *lineIt;
                for (size_t tokenPos = 0; tokenPos < line.size(); ++tokenPos)
                {
                    if (state[tokenPos] && line[tokenPos] == '^')
                    {
                        state[tokenPos - 1] = true;
                        state[tokenPos + 1] = true;
                        state[tokenPos] = false;
                        ++splitCount;
                    }
                }
            }

            outAnswer << splitCount;
        }

        void RunPartTwo(std::ostream& outAnswer) override
        {
            const std::vector<std::string>& lines = GetInputLines();

            std::vector<size_t> state;
            state.resize(lines.front().size(), 0);
            state[lines.front().find('S')] = 1;

            std::vector<size_t> previousState = state;

            for (auto lineIt = std::cbegin(lines) + 1; lineIt != std::cend(lines); ++lineIt)
            {
                std::swap(state, previousState);
                for (size_t tokenPos = 0; tokenPos < state.size(); ++tokenPos)
                {
                    state[tokenPos] = 0;
                }

                const std::string& line = *lineIt;
                for (size_t tokenPos = 0; tokenPos < line.size(); ++tokenPos)
                {
                    if (previousState[tokenPos] == 0)
                    {
                        continue;
                    }

                    if (line[tokenPos] == '^')
                    {
                        state[tokenPos - 1] += previousState[tokenPos];
                        state[tokenPos + 1] += previousState[tokenPos];
                    }
                    else
                    {
                        state[tokenPos] += previousState[tokenPos];
                    }
                }
            }

            size_t timelineCount = 0;
            for (const size_t token : state)
            {
                timelineCount += token;
            }

            outAnswer << timelineCount;
        }

        void RunTimeline(size_t particlePos, size_t lineIndex, size_t& outTimelineCount) const
        {
            ++outTimelineCount;

            const std::vector<std::string>& lines = GetInputLines();
            for (; lineIndex < lines.size(); ++lineIndex)
            {
                if (lines[lineIndex][particlePos] == '^')
                {
                    RunTimeline(particlePos + 1, lineIndex + 1, outTimelineCount);
                    --particlePos;
                }
            }
        }
    };
}

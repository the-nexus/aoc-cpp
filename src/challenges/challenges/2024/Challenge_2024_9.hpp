
#pragma once

#include "challenges/Challenge.hpp"

namespace aoc::challenges
{
    class Challenge_2024_9 final : public Challenge<2024, 9>
    {
        using Super = Challenge<2024, 9>;

    public:
        Challenge_2024_9(std::vector<std::string>&& inputLines)
            : Super(std::move(inputLines))
        {}

        void RunPartOne(std::ostream& outAnswer) override
        {
            std::vector<int> memory;
            BuildMemory(memory);
            CompactData(memory);

            outAnswer << ComputeChecksum(memory);
        }

        void RunPartTwo(std::ostream& outAnswer) override
        {
            Super::RunPartTwo(outAnswer);
        }

        void BuildMemory(std::vector<int>& outMemory) const
        {
            std::string const& line = GetInputLine(0);

            size_t memorySize = 0u;
            std::vector<size_t> spaces;
            spaces.reserve(line.size());

            for (char const token : line)
            {
                spaces.push_back(static_cast<size_t>(token - '0'));
                memorySize += spaces.back();
            }

            outMemory.reserve(memorySize);
            for (size_t spaceIndex = 0u; spaceIndex < spaces.size(); ++spaceIndex)
            {
                int const data = spaceIndex % 2u == 0u ? static_cast<int>(spaceIndex / 2u) : -1;
                for (size_t dataIndex = 0u; dataIndex < spaces[spaceIndex]; ++dataIndex)
                {
                    outMemory.push_back(data);
                }
            }
        }

        static void CompactData(std::vector<int>& memory)
        {
            if (memory.empty())
            {
                return;
            }

            size_t frontIndex = 0u;
            size_t backIndex = memory.size() - 1u;

            while (frontIndex < backIndex)
            {
                if (memory[frontIndex] >= 0)
                {
                    ++frontIndex;
                }
                else if (memory[backIndex] < 0)
                {
                    --backIndex;
                }
                else
                {
                    std::swap(memory[frontIndex], memory[backIndex]);
                }
            }
        }

        static size_t ComputeChecksum(std::vector<int> const& memory)
        {
            size_t checksum = 0u;
            for (size_t dataIndex = 0u; dataIndex < memory.size(); ++dataIndex)
            {
                if (memory[dataIndex] < 0)
                {
                    break;
                }

                checksum += dataIndex * static_cast<size_t>(memory[dataIndex]);
            }
            return checksum;
        }
    };
}

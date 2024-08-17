
#pragma once

#include <deque>

#include <Tools/StringSplitter.h>

#include "Challenges/ChallengeAbstract.h"

namespace AOC::Challenges::Year2022
{
    class Challenge05 final : public ChallengeAbstract
    {
    private:
        struct StackingInstruction
        {
            size_t m_stackSourceIndex = 0;
            size_t m_stackDestinationIndex = 0;
            size_t m_crateCount = 0;
        };

        std::vector<std::deque<char>> m_stacks;
        std::vector<StackingInstruction> m_instructions;

    public:
        Challenge05(std::vector<std::string> const& inputLines)
        {
            // Find the separation between the stacks' initial state and the stacking instructions
            size_t inputDelimiterIndex = 0;
            for (; inputDelimiterIndex < inputLines.size(); ++inputDelimiterIndex)
            {
                if (inputLines[inputDelimiterIndex].size() == 0)
                {
                    break;
                }
            }

            // Setup the stacks
            size_t const lastStackLineIndex = inputDelimiterIndex - 1;
            std::vector<std::string> stackIds;
            Tools::StringSplitter::SplitString(inputLines[lastStackLineIndex], "   ", stackIds);
            m_stacks.resize(stackIds.size());

            for (size_t lineIndex = 0; lineIndex < lastStackLineIndex; ++lineIndex)
            {
                for (size_t characterIndex = 1; characterIndex < inputLines[lineIndex].size(); characterIndex += 4)
                {
                    char const crateId = inputLines[lineIndex][characterIndex];
                    if (crateId >= 'A' && crateId <= 'Z')
                    {
                        size_t const stackIndex = (characterIndex - 1) / 4;
                        m_stacks[stackIndex].push_front(crateId);
                    }
                }
            }

            // Setup the instructions
            size_t const firstInstructionLineIndex = inputDelimiterIndex + 1;
            m_instructions.resize(inputLines.size() - firstInstructionLineIndex);
            for (size_t lineIndex = firstInstructionLineIndex; lineIndex < inputLines.size(); ++lineIndex)
            {
                std::vector<std::string> lineArgs;
                Tools::StringSplitter::SplitString(inputLines[lineIndex], ' ', lineArgs);

                size_t const instructionIndex = lineIndex - firstInstructionLineIndex;
                m_instructions[instructionIndex].m_stackSourceIndex = static_cast<size_t>(atoi(lineArgs[3].c_str()) - 1);
                m_instructions[instructionIndex].m_stackDestinationIndex = static_cast<size_t>(atoi(lineArgs[5].c_str()) - 1);
                m_instructions[instructionIndex].m_crateCount = atoi(lineArgs[1].c_str());
            }
        }

        virtual void Run_PartOne() override
        {
            std::vector<std::deque<char>> stacks = m_stacks;
            for (StackingInstruction const& instruction : m_instructions)
            {
                for (size_t crateCount = 0; crateCount < instruction.m_crateCount; ++crateCount)
                {
                    stacks[instruction.m_stackDestinationIndex].push_back(stacks[instruction.m_stackSourceIndex].back());
                    stacks[instruction.m_stackSourceIndex].pop_back();
                }
            }

            for (std::deque<char> const& stack : stacks)
            {
                if (stack.size() > 0)
                {
                    std::cout << stack.back();
                }
            }
            std::cout << std::endl;
        }

        virtual void Run_PartTwo() override
        {
            std::deque<char> tempStack;
            std::vector<std::deque<char>> stacks = m_stacks;

            for (StackingInstruction const& instruction : m_instructions)
            {
                for (size_t crateCount = 0; crateCount < instruction.m_crateCount; ++crateCount)
                {
                    tempStack.push_back(stacks[instruction.m_stackSourceIndex].back());
                    stacks[instruction.m_stackSourceIndex].pop_back();
                }

                while (tempStack.size() > 0)
                {
                    stacks[instruction.m_stackDestinationIndex].push_back(tempStack.back());
                    tempStack.pop_back();
                }
            }

            for (std::deque<char> const& stack : stacks)
            {
                if (stack.size() > 0)
                {
                    std::cout << stack.back();
                }
            }
            std::cout << std::endl;
        }
    };
}

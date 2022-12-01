#pragma once

#include "../ChallengeAbstract.h"
#include "../../tools/StringTool.h"
#include "../../tools/VectorTool.h"

namespace Year2021
{
    class Challenge02 : public ChallengeAbstract
    {
    private:
        enum EDirectionType
        {
            Forward = 0,
            Up = 1,
            Down = 2
        };

        std::vector<Vector2i> m_instructions;

    public:
        virtual void SetUp(std::vector<std::string> const& inputLines) override
        {
            m_instructions.resize(inputLines.size());

            for (size_t lineIdx = 0; lineIdx < inputLines.size(); ++lineIdx)
            {
                std::vector<std::string> arguments;
                StringTool::SplitString(inputLines[lineIdx], ' ', arguments);

                char const direction = arguments[0][0];
                if (direction == 'f')
                {
                    m_instructions[lineIdx][0] = Forward;
                }
                else if (direction == 'u')
                {
                    m_instructions[lineIdx][0] = Up;
                }
                else if (direction == 'd')
                {
                    m_instructions[lineIdx][0] = Down;
                }

                m_instructions[lineIdx][1] = atoi(arguments[1].c_str());
            }
        }

        virtual void Run_PartOne() override
        {
            Vector2i position;
            for (Vector2i const& instruction : m_instructions)
            {
                switch (instruction[0])
                {
                case Forward:
                    position[0] += instruction[1];
                    break;

                case Up:
                    position[1] -= instruction[1];
                    break;

                case Down:
                    position[1] += instruction[1];
                    break;

                default:
                    break;
                }
            }

            std::cout << position[0] * position[1] << std::endl;
        }

        virtual void Run_PartTwo() override
        {
            Vector2i position;
            int aim = 0;
            for (Vector2i const& instruction : m_instructions)
            {
                switch (instruction[0])
                {
                case Forward:
                    position[0] += instruction[1];
                    position[1] += instruction[1] * aim;
                    break;

                case Up:
                    aim -= instruction[1];
                    break;

                case Down:
                    aim += instruction[1];
                    break;

                default:
                    break;
                }
            }

            std::cout << position[0] * position[1] << std::endl;
        }

        virtual void CleanUp() override {}
    };
}

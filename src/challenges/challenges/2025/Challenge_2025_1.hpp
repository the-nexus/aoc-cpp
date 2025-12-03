
#pragma once

#include "challenges/Challenge.hpp"

namespace aoc::challenges
{
    class Challenge_2025_1 final : public Challenge<2025, 1>
    {
        using Super = Challenge<2025, 1>;

    public:
        Challenge_2025_1(std::vector<std::string>&& inputLines)
            : Super(std::move(inputLines))
        {}

        void RunPartOne(std::ostream& outAnswer) override
        {
            constexpr int maxCount = 100;
            int counter = 50;
            int password = 0;

            std::vector<std::string> const& lines = GetInputLines();
            for (const std::string& line : lines)
            {
                int steps = std::stoi(line.substr(1));

                if (line[0] == 'L')
                {
                    if (steps >= counter)
                    {
                        steps -= counter;
                        counter = 0;

                        steps %= maxCount;
                        if (steps > 0)
                        {
                            counter = maxCount - steps;
                        }
                    }
                    else
                    {
                        counter -= steps;
                    }
                }
                else
                {
                    int const counterInverse = maxCount - counter;
                    if (steps >= counterInverse)
                    {
                        steps -= counterInverse;
                        counter = 0;

                        steps %= maxCount;
                        if (steps > 0)
                        {
                            counter = steps;
                        }
                    }
                    else
                    {
                        counter += steps;
                    }
                }

                if (counter == 0)
                {
                    ++password;
                }
            }

            outAnswer << password;
        }

        void RunPartTwo(std::ostream& outAnswer) override
        {
            constexpr int maxCount = 100;
            int counter = 50;
            int password = 0;

            std::vector<std::string> const& lines = GetInputLines();
            // 

            for (const std::string& line : lines)
            {
                int steps = std::stoi(line.substr(1));

                if (line[0] == 'L')
                {
                    for (int step = 0; step < steps; ++step)
                    {
                        --counter;

                        if (counter < 0)
                        {
                            counter += maxCount;
                        }
                        
                        if (counter == 0)
                        {
                            ++password;
                        }
                    }

                    // if (steps >= counter)
                    // {
                    //     steps -= counter;
                    //     counter = 0;
                    //     ++password;

                    //     const int wraps = steps / maxCount;
                    //     password += wraps;

                    //     steps %= maxCount;
                    //     if (steps > 0)
                    //     {
                    //         counter = maxCount - steps;
                    //     }
                    // }
                    // else
                    // {
                    //     counter -= steps;
                    // }
                }
                else
                {
                    for (int step = 0; step < steps; ++step)
                    {
                        ++counter;

                        if (counter >= maxCount)
                        {
                            counter -= maxCount;
                        }

                        if (counter == 0)
                        {
                            ++password;
                        }
                    }

                    // int const counterInverse = maxCount - counter;
                    // if (steps >= counterInverse)
                    // {
                    //     steps -= counterInverse;
                    //     counter = 0;
                    //     ++password;

                    //     const int wraps = steps / maxCount;
                    //     password += wraps;

                    //     steps %= maxCount;
                    //     if (steps > 0)
                    //     {
                    //         counter = steps;
                    //     }
                    // }
                    // else
                    // {
                    //     counter += steps;
                    // }
                }
            }

            outAnswer << password;
        }
    };
}

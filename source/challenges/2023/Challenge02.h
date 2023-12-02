#pragma once

#include "../ChallengeAbstract.h"

namespace Year2023
{
    class Challenge02 : public ChallengeAbstract
    {
    private:
        struct Hand
        {
            int m_red = 0;
            int m_green = 0;
            int m_blue = 0;
        };

        struct Game
        {
            std::vector<Hand> m_hands;
            int m_id = 0;
        };

        std::vector<Game> m_games;

    public:
        virtual void SetUp(std::vector<std::string> const& inputLines) override
        {
            m_games.reserve(inputLines.size());
            for (std::string const& line : inputLines)
            {
                Game& game = m_games.emplace_back();

                std::vector<std::string> lineSplit;
                StringTool::SplitString(line, ": ", lineSplit);

                size_t const idPos = lineSplit[0].find_first_of(' ') + 1;
                game.m_id = atoi(lineSplit[0].substr(idPos).c_str());

                std::vector<std::string> handsSplit;
                StringTool::SplitString(lineSplit[1], "; ", handsSplit);

                game.m_hands.reserve(handsSplit.size());
                for (std::string const& handStr : handsSplit)
                {
                    Hand& hand = game.m_hands.emplace_back();

                    std::vector<std::string> cubesSplit;
                    StringTool::SplitString(handStr, ", ", cubesSplit);

                    for (std::string const& cubesStr : cubesSplit)
                    {
                        size_t const splitPos = cubesStr.find(' ');
                        int const cubeCount = atoi(cubesStr.substr(0, splitPos).c_str());

                        switch (cubesStr[splitPos + 1])
                        {
                        case 'r': hand.m_red = cubeCount; break;
                        case 'g': hand.m_green = cubeCount; break;
                        case 'b': hand.m_blue = cubeCount; break;
                        default: break;
                        }
                    }
                }
            }
        }

        virtual void Run_PartOne() override
        {
            int constexpr red = 12;
            int constexpr green = 13;
            int constexpr blue = 14;

            int idSum = 0;

            for (Game const& game : m_games)
            {
                if (IsValidGame(game, red, green, blue))
                {
                    idSum += game.m_id;
                }
            }

            std::cout << idSum << std::endl;
        }

        virtual void Run_PartTwo() override
        {
            int powerSum = 0;

            for (Game const& game : m_games)
            {
                powerSum += GetGamePower(game);
            }

            std::cout << powerSum << std::endl;
        }

        virtual void CleanUp() override {}

    private:
        static bool IsValidGame(Game const& game, int const red, int const green, int const blue)
        {
            for (Hand const& hand : game.m_hands)
            {
                if (hand.m_red > red ||
                    hand.m_green > green ||
                    hand.m_blue > blue)
                {
                    return false;
                }
            }

            return true;
        }

        static int GetGamePower(Game const& game)
        {
            int red = 0;
            int green = 0;
            int blue = 0;

            for (Hand const& hand : game.m_hands)
            {
                if (hand.m_red > red) red = hand.m_red;
                if (hand.m_green > green) green = hand.m_green;
                if (hand.m_blue > blue) blue = hand.m_blue;
            }

            return red * green * blue;
        }
    };
}

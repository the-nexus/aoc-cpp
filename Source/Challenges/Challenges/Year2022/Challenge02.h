
#pragma once

#include "Challenges/ChallengeAbstract.h"

namespace AOC::Challenges::Year2022
{
    class Challenge02 final : public ChallengeAbstract
    {
    private:
        enum class EGameShapeType : int
        {
            Rock = 1,
            Paper = 2,
            Scissors = 3
        };

        enum class EGameResultType : int
        {
            Lose = 0,
            Draw = 3,
            Win = 6
        };

        std::vector<std::pair<EGameShapeType, int>> m_tournamentData;

    public:
        Challenge02(std::vector<std::string> const& inputLines)
        {
            m_tournamentData.resize(inputLines.size());
            for (size_t lineIndex = 0; lineIndex < inputLines.size(); ++lineIndex)
            {
                m_tournamentData[lineIndex].first = static_cast<EGameShapeType>(inputLines[lineIndex][0] - 'A' + 1);
                m_tournamentData[lineIndex].second = static_cast<int>(inputLines[lineIndex][2] - 'X');
            }
        }

        virtual void Run_PartOne() override
        {
            EGameShapeType const shapeDecoder[3] = { EGameShapeType::Rock, EGameShapeType::Paper, EGameShapeType::Scissors };

            int score = 0;
            for (std::pair<EGameShapeType, int> const& gameData : m_tournamentData)
            {
                EGameShapeType const decodedShape = shapeDecoder[gameData.second];
                score += static_cast<int>(decodedShape);
                score += static_cast<int>(GetGameResult(decodedShape, gameData.first));
            }

            std::cout << score << std::endl;
        }

        virtual void Run_PartTwo() override
        {
            EGameResultType const resultDecoder[3] = { EGameResultType::Lose, EGameResultType::Draw, EGameResultType::Win };
            std::vector<EGameShapeType> const testShapes = { EGameShapeType::Rock, EGameShapeType::Paper, EGameShapeType::Scissors };

            int score = 0;
            for (std::pair<EGameShapeType, int> const& gameData : m_tournamentData)
            {
                EGameResultType const decodedResult = resultDecoder[gameData.second];
                score += static_cast<int>(decodedResult);

                for (EGameShapeType const testShape : testShapes)
                {
                    if (decodedResult == GetGameResult(testShape, gameData.first))
                    {
                        score += static_cast<int>(testShape);
                    }
                }
            }

            std::cout << score << std::endl;
        }

    private:
        EGameResultType GetGameResult(EGameShapeType const firstPlayerShape, EGameShapeType const secondPlayerShape) const
        {
            if (firstPlayerShape == secondPlayerShape)
            {
                return EGameResultType::Draw;
            }
            else
            {
                bool isWin = false;
                switch (secondPlayerShape)
                {
                case EGameShapeType::Rock: isWin = firstPlayerShape == EGameShapeType::Paper; break;
                case EGameShapeType::Paper: isWin = firstPlayerShape == EGameShapeType::Scissors; break;
                case EGameShapeType::Scissors: isWin = firstPlayerShape == EGameShapeType::Rock; break;
                default: break;
                }

                return isWin ? EGameResultType::Win : EGameResultType::Lose;
            }
        }
    };
}

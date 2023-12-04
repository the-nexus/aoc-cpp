#pragma once

#include "../ChallengeAbstract.h"

namespace Year2023
{
    class Challenge04 : public ChallengeAbstract
    {
    private:
        struct Card
        {
            std::set<int> m_winningNumbers;
            std::set<int> m_ownedNumbers;
            int m_id = 0;
            int m_matchCount = 0;
            int m_copyCount = 1;
        };

        std::vector<Card> m_cards;

    public:
        virtual void SetUp(std::vector<std::string> const& inputLines) override
        {
            m_cards.reserve(inputLines.size());
            for (std::string const& line : inputLines)
            {
                std::vector<std::string> lineSplit;
                StringTool::SplitString(line, ": ", lineSplit);

                std::vector<std::string> numbersSplit;
                StringTool::SplitString(lineSplit[1], " | ", numbersSplit);

                Card& card = m_cards.emplace_back();

                size_t const idStartPos = lineSplit[0].find_last_of(' ') + 1;
                card.m_id = atoi(lineSplit[0].substr(idStartPos).c_str());

                ParseNumberSet(numbersSplit[0], card.m_winningNumbers);
                ParseNumberSet(numbersSplit[1], card.m_ownedNumbers);

                for (int const number : card.m_winningNumbers)
                {
                    if (card.m_ownedNumbers.find(number) != card.m_ownedNumbers.cend())
                    {
                        ++card.m_matchCount;
                    }
                }
            }
        }

        virtual void Run_PartOne() override
        {
            int pointSum = 0;
            for (Card const& card : m_cards)
            {
                pointSum += GetCardPoints(card);
            }

            std::cout << pointSum << std::endl;
        }

        virtual void Run_PartTwo() override
        {
            int totalCardCount = 0;
            for (size_t cardIndex = 0; cardIndex < m_cards.size(); ++cardIndex)
            {
                Card& card = m_cards[cardIndex];
                totalCardCount += card.m_copyCount;

                size_t cardsToCopyEnd = cardIndex + card.m_matchCount + 1;
                if (cardsToCopyEnd > m_cards.size())
                {
                    cardsToCopyEnd = m_cards.size();
                }

                for (size_t cardToCopyIndex = cardIndex + 1; cardToCopyIndex < cardsToCopyEnd; ++cardToCopyIndex)
                {
                    m_cards[cardToCopyIndex].m_copyCount += card.m_copyCount;
                }
            }

            std::cout << totalCardCount << std::endl;
        }

        virtual void CleanUp() override {}

    private:
        static void ParseNumberSet(std::string const& numberStr, std::set<int>& numberSet)
        {
            int number = 0;
            for (char const item : numberStr)
            {
                if (item >= '0' && item <= '9')
                {
                    number = number * 10 + static_cast<int>(item - '0');
                }
                else if (number != 0)
                {
                    numberSet.insert(number);
                    number = 0;
                }
            }

            numberSet.insert(number);
        }

        static int GetCardPoints(Card const& card)
        {
            if (card.m_matchCount == 0)
            {
                return 0;
            }
            else
            {
                return static_cast<int>(powf(2.f, card.m_matchCount - 1));
            }
        }
    };
}

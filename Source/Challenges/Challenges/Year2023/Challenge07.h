
#pragma once

#include "Challenges/ChallengeAbstract.h"

namespace AOC::Challenges::Year2023
{
    class Challenge07 final : public ChallengeAbstract
    {
    private:

        enum class HandType
        {
            HighCard,
            OnePair,
            TwoPair,
            ThreeOfAKind,
            FullHouse,
            FourOfAKind,
            FiveOfAKind
        };

        struct Hand
        {
            std::string m_cards;
            unsigned long long m_bid = 0;
            HandType m_type = HandType::HighCard;
        };

        std::vector<Hand> m_hands;

    public:
        Challenge07(std::vector<std::string> const& inputLines)
        {
            m_hands.reserve(inputLines.size());
            for (std::string const& line : inputLines)
            {
                std::vector<std::string> handSplit;
                Tools::StringSplitter::SplitString(line, ' ', handSplit);

                Hand& hand = m_hands.emplace_back();
                hand.m_cards = handSplit[0];
                hand.m_bid = atoll(handSplit[1].c_str());
                hand.m_type = GetHandType(hand.m_cards);
            }
        }

        virtual void Run_PartOne() override
        {
            std::cout << GetWinnings(m_hands, false) << std::endl;
        }

        virtual void Run_PartTwo() override
        {
            std::vector<Hand> improvedHands = m_hands;
            for (Hand& hand : improvedHands)
            {
                ImproveHand(hand);
            }

            std::cout << GetWinnings(improvedHands, true) << std::endl;
        }

    private:
        static unsigned long long GetWinnings(std::vector<Hand>& hands, bool const useJokers)
        {
            std::sort(hands.begin(), hands.end(), [&useJokers](Hand const& lhs, Hand const& rhs) { return CompareHands(lhs, rhs, useJokers) < 0; });

            unsigned long long winnings = 0;
            for (size_t rank = 0; rank < hands.size(); ++rank)
            {
                winnings += (rank + 1) * hands[rank].m_bid;
            }

            return winnings;
        }

        static void ImproveHand(Hand& hand)
        {
            std::map<char, int> cardCountMap;
            CountCards(hand.m_cards, cardCountMap);

            auto it = cardCountMap.find('J');
            if (it == cardCountMap.cend() || it->second == 0)
            {
                return;
            }

            switch (hand.m_type)
            {
            case HandType::HighCard: ImproveHighCard(hand, cardCountMap, it->second); break;
            case HandType::OnePair: ImproveOnePair(hand, cardCountMap, it->second); break;
            case HandType::TwoPair: ImproveTwoPair(hand, cardCountMap, it->second); break;
            case HandType::ThreeOfAKind: ImproveThreeOfAKind(hand, cardCountMap, it->second); break;
            case HandType::FullHouse: ImproveFullHouse(hand, cardCountMap); break;
            case HandType::FourOfAKind: ImproveFourOfAKind(hand, cardCountMap); break;
            case HandType::FiveOfAKind: ImproveFiveOfAKind(hand); break;
            }
        }

        static void ImproveHighCard(Hand& hand, std::map<char, int> const& cardCountMap, int const jokerCount)
        {
            char replacementCard = 'J';
            int replacementCardValue = -1;

            for (std::pair<char, int> const& cardCount : cardCountMap)
            {
                if (cardCount.first != 'J')
                {
                    int const cardValue = GetCardValue(cardCount.first, true);
                    if (cardValue > replacementCardValue)
                    {
                        replacementCard = cardCount.first;
                    }
                }
            }

            hand.m_type = HandType::OnePair;
        }

        static void ImproveOnePair(Hand& hand, std::map<char, int> const& cardCountMap, int const jokerCount)
        {
            char replacementCard = 'J';

            if (jokerCount == 2)
            {
                int replacementCardValue = -1;
                for (std::pair<char, int> const& cardCount : cardCountMap)
                {
                    if (cardCount.first != 'J')
                    {
                        int const cardValue = GetCardValue(cardCount.first, true);
                        if (cardValue > replacementCardValue)
                        {
                            replacementCard = cardCount.first;
                        }
                    }
                }
            }
            else
            {
                for (std::pair<char, int> const& cardCount : cardCountMap)
                {
                    if (cardCount.first != 'J' && cardCount.second == 2)
                    {
                        replacementCard = cardCount.first;
                        break;
                    }
                }
            }

            hand.m_type = HandType::ThreeOfAKind;
        }

        static void ImproveTwoPair(Hand& hand, std::map<char, int> const& cardCountMap, int const jokerCount)
        {
            char replacementCard = 'J';
            if (jokerCount == 2)
            {
                for (std::pair<char, int> const& cardCount : cardCountMap)
                {
                    if (cardCount.first != 'J' && cardCount.second == 2)
                    {
                        replacementCard = cardCount.first;
                        break;
                    }
                }
                hand.m_type = HandType::FourOfAKind;
            }
            else
            {
                int replacementCardValue = -1;
                for (std::pair<char, int> const& cardCount : cardCountMap)
                {
                    if (cardCount.first != 'J')
                    {
                        int const cardValue = GetCardValue(cardCount.first, true);
                        if (cardValue > replacementCardValue)
                        {
                            replacementCard = cardCount.first;
                        }
                    }
                }
                hand.m_type = HandType::FullHouse;
            }
        }

        static void ImproveThreeOfAKind(Hand& hand, std::map<char, int> const& cardCountMap, int const jokerCount)
        {
            char replacementCard = 'J';

            if (jokerCount == 3)
            {
                int replacementCardValue = -1;
                for (std::pair<char, int> const& cardCount : cardCountMap)
                {
                    if (cardCount.first != 'J')
                    {
                        int const cardValue = GetCardValue(cardCount.first, true);
                        if (cardValue > replacementCardValue)
                        {
                            replacementCard = cardCount.first;
                        }
                    }
                }
            }
            else
            {
                for (std::pair<char, int> const& cardCount : cardCountMap)
                {
                    if (cardCount.first != 'J' && cardCount.second == 3)
                    {
                        replacementCard = cardCount.first;
                        break;
                    }
                }
            }

            hand.m_type = HandType::FourOfAKind;
        }

        static void ImproveFullHouse(Hand& hand, std::map<char, int> const& cardCountMap)
        {
            char replacementCard = 'J';

            for (std::pair<char, int> const& cardCount : cardCountMap)
            {
                if (cardCount.first != 'J')
                {
                    replacementCard = cardCount.first;
                    break;
                }
            }

            hand.m_type = HandType::FiveOfAKind;
        }

        static void ImproveFourOfAKind(Hand& hand, std::map<char, int> const& cardCountMap)
        {
            char replacementCard = 'J';

            for (std::pair<char, int> const& cardCount : cardCountMap)
            {
                if (cardCount.first != 'J')
                {
                    replacementCard = cardCount.first;
                    break;
                }
            }

            hand.m_type = HandType::FiveOfAKind;
        }

        static void ImproveFiveOfAKind(Hand& hand)
        {
            hand.m_cards = "AAAAA";
            hand.m_type = HandType::FiveOfAKind;
        }

        static HandType GetHandType(std::string const& cards)
        {
            std::map<char, int> cardCountMap;
            CountCards(cards, cardCountMap);

            int fiveCount = 0;
            int fourCount = 0;
            int threeCount = 0;
            int twoCount = 0;

            for (std::pair<char, int> const& cardCount : cardCountMap)
            {
                if (cardCount.second == 5)
                {
                    ++fiveCount;
                }
                else if (cardCount.second == 4)
                {
                    ++fourCount;
                }
                else if (cardCount.second == 3)
                {
                    ++threeCount;
                }
                else if (cardCount.second == 2)
                {
                    ++twoCount;
                }
            }

            if (fiveCount > 0)
            {
                return HandType::FiveOfAKind;
            }

            if (fourCount > 0)
            {
                return HandType::FourOfAKind;
            }

            if (threeCount > 0)
            {
                return twoCount > 0 ? HandType::FullHouse : HandType::ThreeOfAKind;
            }

            if (twoCount > 0)
            {
                return twoCount > 1 ? HandType::TwoPair : HandType::OnePair;
            }

            return HandType::HighCard;
        }

        static void CountCards(std::string const& cards, std::map<char, int>& outCardCountMap)
        {
            for (char const card : cards)
            {
                auto it = outCardCountMap.find(card);
                if (it != outCardCountMap.cend())
                {
                    it->second += 1;
                }
                else
                {
                    outCardCountMap.emplace(card, 1);
                }
            }
        }

        static int CompareHands(Hand const& lhs, Hand const& rhs, bool const useJokers)
        {
            if (lhs.m_type != rhs.m_type)
            {
                return lhs.m_type > rhs.m_type ? 1 : -1;
            }

            for (size_t cardIndex = 0; cardIndex < lhs.m_cards.size(); ++cardIndex)
            {
                if (lhs.m_cards[cardIndex] != rhs.m_cards[cardIndex])
                {
                    return CompareCards(lhs.m_cards[cardIndex], rhs.m_cards[cardIndex], useJokers);
                }
            }

            return 0;
        }

        static int CompareCards(char const lhs, char const rhs, bool const useJokers)
        {
            int const lhsValue = GetCardValue(lhs, useJokers);
            int const rhsValue = GetCardValue(rhs, useJokers);

            if (lhsValue != rhsValue)
            {
                return lhsValue > rhsValue ? 1 : -1;
            }

            return 0;
        }

        static int GetCardValue(char const card, bool const useJokers)
        {
            switch (card)
            {
            case 'A': return 14;
            case 'K': return 13;
            case 'Q': return 12;
            case 'J': return useJokers ? -1 : 11;
            case 'T': return 10;
            default:  return static_cast<int>(card - '0');
            }
        }
    };
}

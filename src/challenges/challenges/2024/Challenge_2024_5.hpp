
#pragma once

#include "challenges/Challenge.hpp"

#include <algorithm>
#include <set>
#include <unordered_map>

namespace aoc::challenges
{
    class Challenge_2024_5 final : public Challenge<2024, 5>
    {
        using Super = Challenge<2024, 5>;

    public:
        Challenge_2024_5(std::vector<std::string>&& inputLines)
            : Super(std::move(inputLines)) 
        {}

        void RunPartOne(std::ostream& outAnswer) override
        {
            std::unordered_map<unsigned int, std::set<unsigned int>> rules;
            std::vector<std::vector<unsigned int>> books;
            ParseInput(rules, books);

            unsigned int pageSum = 0u;
            for (std::vector<unsigned int> const& book : books)
            {
                if (IsValidBook(rules, book))
                {
                    pageSum += book[book.size() / 2u];
                }
            }

            outAnswer << pageSum;
        }

        void RunPartTwo(std::ostream& outAnswer) override
        {
            std::unordered_map<unsigned int, std::set<unsigned int>> rules;
            std::vector<std::vector<unsigned int>> books;
            ParseInput(rules, books);

            unsigned int pageSum = 0u;
            for (std::vector<unsigned int>& book : books)
            {
                if (IsValidBook(rules, book))
                {
                    continue;
                }

                std::sort(std::begin(book), std::end(book), [this, &rules](unsigned int const lhs, unsigned int const rhs) {
                    return HasRule(rules, lhs, rhs);
                });
                pageSum += book[book.size() / 2u];
            }

            outAnswer << pageSum;
        }

        void ParseInput(std::unordered_map<unsigned int, std::set<unsigned int>>& outRules, std::vector<std::vector<unsigned int>>& outBooks) const
        {
            auto lineIt = std::cbegin(GetInputLines());
            auto const endIt = std::cend(GetInputLines());

            // Parse rules
            for (; lineIt != endIt; ++lineIt)
            {
                if (lineIt->empty())
                {
                    ++lineIt;
                    break;
                }

                unsigned int firstPage = static_cast<unsigned int>((*lineIt)[0] - '0') * 10u + static_cast<unsigned int>((*lineIt)[1] - '0');
                unsigned int secondPage = static_cast<unsigned int>((*lineIt)[3] - '0') * 10u + static_cast<unsigned int>((*lineIt)[4] - '0');

                auto result = outRules.try_emplace(firstPage);
                result.first->second.insert(secondPage);
            }

            // Parse books
            outBooks.reserve(std::distance(lineIt, endIt));
            for (; lineIt != endIt; ++lineIt)
            {
                size_t const separatorCount = std::count(std::cbegin(*lineIt), std::cend(*lineIt), ',');

                std::vector<unsigned int>& book = outBooks.emplace_back();
                book.reserve(separatorCount);
                book.push_back(0u);

                for (char const token : *lineIt)
                {
                    if (token == ',')
                    {
                        book.push_back(0u);
                        continue;
                    }

                    unsigned int& page = book.back();
                    page = page * 10u + static_cast<unsigned int>(token - '0');
                }
            }
        }

        bool IsValidBook(std::unordered_map<unsigned int, std::set<unsigned int>> const& rules, std::vector<unsigned int> const& book) const
        {
            for (auto firstPageIt = std::cbegin(book); firstPageIt != std::cend(book); ++firstPageIt)
            {
                for (auto secondPageIt = firstPageIt + 1; secondPageIt != std::cend(book); ++secondPageIt)
                {
                    if (HasRule(rules, *secondPageIt, *firstPageIt))
                    {
                        return false;
                    }
                }
            }

            return true;
        }

        bool HasRule(std::unordered_map<unsigned int, std::set<unsigned int>> const& rules, unsigned int const lhs, unsigned int const rhs) const
        {
            auto const lhsIt = rules.find(lhs);
            if (lhsIt == std::cend(rules))
            {
                return false;
            }

            auto const rhsIt = lhsIt->second.find(rhs);
            if (rhsIt == std::cend(lhsIt->second))
            {
                return false;
            }

            return true;
        }
    };
}

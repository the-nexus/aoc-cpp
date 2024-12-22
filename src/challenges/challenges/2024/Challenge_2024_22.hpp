
#pragma once

#include "challenges/Challenge.hpp"

#include <future>
#include <mutex>
#include <map>
#include <set>

namespace aoc::challenges
{
    class Challenge_2024_22 final : public Challenge<2024, 22>
    {
        using Super = Challenge<2024, 22>;
        struct Sequence
        {
            int _data[4] = { 0, 0, 0, 0 };

            int& operator[](size_t const index) { return _data[index]; }
            int const& operator[](size_t const index) const { return _data[index]; }

            bool operator==(Sequence const& other) const
            {
                return _data[0] == other[0]
                    && _data[1] == other[1]
                    && _data[2] == other[2]
                    && _data[3] == other[3];
            }

            bool operator<(Sequence const& other) const
            {
                if (_data[0] != other[0]) return _data[0] < other[0];
                if (_data[1] != other[1]) return _data[1] < other[1];
                if (_data[2] != other[2]) return _data[2] < other[2];
                return _data[3] < other[3];
            }
        };

    public:
        Challenge_2024_22(std::vector<std::string>&& inputLines)
            : Super(std::move(inputLines))
        {}

        void RunPartOne(std::ostream& outAnswer) override
        {
            std::vector<std::string> const& lines = GetInputLines();

            std::vector<std::future<unsigned int>> allSecretNumbersTasks;
            allSecretNumbersTasks.reserve(lines.size());

            for (size_t taskIndex = 0u; taskIndex < lines.size(); ++taskIndex)
            {
                auto task = [](unsigned int const initialSecretNumber)
                {
                    std::vector<unsigned int> secretNumbers;
                    GenerateSecretNumbers(initialSecretNumber, secretNumbers);
                    return secretNumbers.back();
                };

                allSecretNumbersTasks.emplace_back(std::async(task, std::stoul(lines[taskIndex])));
            }

            unsigned long long sum = 0;
            for (std::future<unsigned int>& task : allSecretNumbersTasks)
            {
                task.wait();
                sum += task.get();
            }

            outAnswer << sum;
        }

        void RunPartTwo(std::ostream& outAnswer) override
        {
            std::vector<std::string> const& lines = GetInputLines();

            std::vector<std::future<void>> allProfitSequencesTasks;
            allProfitSequencesTasks.reserve(lines.size());

            std::vector<std::map<Sequence, int>> allProfitSequences;
            allProfitSequences.resize(lines.size());

            for (size_t taskIndex = 0u; taskIndex < lines.size(); ++taskIndex)
            {
                auto task = [](unsigned int const initialSecretNumber, std::map<Sequence, int>& outProfitSequences)
                {
                    std::vector<unsigned int> secretNumbers;
                    GenerateSecretNumbers(initialSecretNumber, secretNumbers);
                    EvaluateProfitSequences(secretNumbers, outProfitSequences);
                };

                allProfitSequencesTasks.emplace_back(std::async(task, std::stoul(lines[taskIndex]), std::ref(allProfitSequences[taskIndex])));
            }

            std::set<Sequence> uniqueSequences;
            for (size_t taskIndex = 0u; taskIndex < allProfitSequencesTasks.size(); ++taskIndex)
            {
                allProfitSequencesTasks[taskIndex].wait();
                for (std::pair<Sequence, int> const& profitSequence : allProfitSequences[taskIndex])
                {
                    if (!uniqueSequences.contains(profitSequence.first))
                    {
                        uniqueSequences.emplace(profitSequence.first);
                    }
                }
            }

            std::vector<std::future<int>> allTotalProfitTasks;
            allTotalProfitTasks.reserve(uniqueSequences.size());

            for (Sequence const& uniqueSequence : uniqueSequences)
            {
                auto task = [&allProfitSequences](Sequence const& uniqueSequence)
                {
                    int profit = 0;
                    for (std::map<Sequence, int> const& profitSequences : allProfitSequences)
                    {
                        auto const it = profitSequences.find(uniqueSequence);
                        if (it != std::cend(profitSequences))
                        {
                            profit += it->second;
                        }
                    }
                    return profit;
                };

                allTotalProfitTasks.emplace_back(std::async(task, uniqueSequence));
            }

            int bestProfit = 0;
            for (std::future<int>& task : allTotalProfitTasks)
            {
                task.wait();
                int const profit = task.get();
                if (profit > bestProfit)
                {
                    bestProfit = profit;
                }
            }

            outAnswer << bestProfit;
        }

        static void GenerateSecretNumbers(unsigned int secretNumber, std::vector<unsigned int>& outSecretNumbers)
        {
            size_t constexpr amountToGenerate = 2001;

            outSecretNumbers.resize(amountToGenerate);
            outSecretNumbers[0] = secretNumber;

            for (size_t numberIndex = 1u; numberIndex < amountToGenerate; ++numberIndex)
            {
                secretNumber = GenerateSecretNumber(secretNumber);
                outSecretNumbers[numberIndex] = secretNumber;
            }
        }

        static unsigned int GenerateSecretNumber(unsigned int secretNumber)
        {
            unsigned int constexpr pruner = 16777216;

            unsigned int constexpr firstMixer = 64;
            unsigned int const firstModifier = secretNumber * firstMixer;
            secretNumber = (secretNumber ^ firstModifier) % pruner;

            unsigned int constexpr secondMixer = 32;
            unsigned int const secondModifier = secretNumber / secondMixer;
            secretNumber = (secretNumber ^ secondModifier) % pruner;

            unsigned int constexpr thirdMixer = 2048;
            unsigned int const thirdModifier = secretNumber * thirdMixer;
            secretNumber = (secretNumber ^ thirdModifier) % pruner;

            return secretNumber;
        }

        static void EvaluateProfitSequences(std::vector<unsigned int> const& secretNumbers, std::map<Sequence, int>& outProfitSequences)
        {
            std::vector<int> prices;
            prices.resize(secretNumbers.size());
            for (size_t numberIndex = 0u; numberIndex < secretNumbers.size(); ++numberIndex)
            {
                prices[numberIndex] = static_cast<int>(secretNumbers[numberIndex] % 10u);
            }

            std::vector<int> priceChanges;
            priceChanges.resize(prices.size() - 1u);
            for (size_t priceIndex = 1u; priceIndex < prices.size(); ++priceIndex)
            {
                priceChanges[priceIndex - 1u] = prices[priceIndex] - prices[priceIndex - 1u];
            }

            Sequence currentSequence = { 0, priceChanges[0], priceChanges[1], priceChanges[2] };
            for (size_t priceChangeIndex = 3u; priceChangeIndex < priceChanges.size(); ++priceChangeIndex)
            {
                std::swap(currentSequence[0], currentSequence[1]);
                std::swap(currentSequence[1], currentSequence[2]);
                std::swap(currentSequence[2], currentSequence[3]);
                currentSequence[3] = priceChanges[priceChangeIndex];

                outProfitSequences.try_emplace(currentSequence, prices[priceChangeIndex + 1u]);
            }
        }
    };
}

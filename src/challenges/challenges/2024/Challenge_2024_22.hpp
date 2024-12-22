
#pragma once

#include "challenges/Challenge.hpp"

#include <future>
#include <mutex>
#include <map>

namespace aoc::challenges
{
    class Challenge_2024_22 final : public Challenge<2024, 22>
    {
        using Super = Challenge<2024, 22>;

    public:
        Challenge_2024_22(std::vector<std::string>&& inputLines)
            : Super(std::move(inputLines))
        {}

        void RunPartOne(std::ostream& outAnswer) override
        {
            std::mutex sumMutex;
            unsigned long long sum = 0;
            auto monkeyTask = [&sum, &sumMutex](unsigned int const initialSecretNumber)
            {
                std::vector<unsigned int> secretNumbers;
                GenerateSecretNumbers(initialSecretNumber, secretNumbers);

                std::lock_guard<std::mutex> lock(sumMutex);
                sum += secretNumbers.back();
            };

            std::vector<std::future<void>> monkeys;
            monkeys.reserve(GetInputLines().size());

            for (std::string const& line : GetInputLines())
            {
                monkeys.emplace_back(std::async(monkeyTask, std::stoull(line)));
            }

            for (std::future<void> const& monkey : monkeys)
            {
                monkey.wait();
            }

            outAnswer << sum;
        }

        void RunPartTwo(std::ostream& outAnswer) override
        {
            Super::RunPartTwo(outAnswer);
        }

        static void GenerateSecretNumbers(unsigned int secretNumber, std::vector<unsigned int>& outSecretNumbers)
        {
            size_t constexpr amountToGenerate = 2000;

            outSecretNumbers.resize(amountToGenerate);

            for (size_t numberIndex = 0u; numberIndex < amountToGenerate; ++numberIndex)
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
    };
}

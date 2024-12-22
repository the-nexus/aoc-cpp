
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
        using Sequence = std::tuple<int, int, int, int>;

    public:
        Challenge_2024_22(std::vector<std::string>&& inputLines)
            : Super(std::move(inputLines))
        {}

        void RunPartOne(std::ostream& outAnswer) override
        {
            std::vector<std::string> const& lines = GetInputLines();

            std::vector<std::future<void>> allSecretNumbersTasks;
            allSecretNumbersTasks.reserve(lines.size());

            std::vector<std::vector<unsigned int>> allSecretNumbers;
            allSecretNumbers.resize(lines.size());

            for (size_t taskIndex = 0u; taskIndex < lines.size(); ++taskIndex)
            {
                auto task = [](unsigned int const initialSecretNumber, std::vector<unsigned int>& outSecretNumbers)
                {
                    GenerateSecretNumbers(initialSecretNumber, outSecretNumbers);
                };

                allSecretNumbersTasks.emplace_back(std::async(task, std::stoul(lines[taskIndex]), std::ref(allSecretNumbers[taskIndex])));
            }

            unsigned long long sum = 0;
            for (size_t taskIndex = 0u; taskIndex < allSecretNumbersTasks.size(); ++taskIndex)
            {
                allSecretNumbersTasks[taskIndex].wait();
                sum += allSecretNumbers[taskIndex].back();
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


#pragma once

#include <ostream>
#include <string>
#include <vector>

#include "Challenges/ChallengeIdentifier.hpp"

namespace AOC::Challenges
{
    class IChallenge
    {
    public:
        virtual ~IChallenge() = default;
        virtual void RunPartOne(std::ostream& outAnswer) = 0;
        virtual void RunPartTwo(std::ostream& outAnswer) = 0;
    };

    template <int YearN, int DayN>
    class Challenge : public IChallenge
    {
        std::vector<std::string> m_inputLines;

    public:
        static constexpr ChallengeIdentifier GetIdentifier() { return { YearN, DayN }; }

        Challenge(std::vector<std::string>&& inputLines)
            : m_inputLines(std::move(inputLines))
        {
            inputLines = {};
        }

        void RunPartOne(std::ostream& outAnswer) override { outAnswer << "PART ONE NOT IMPLEMENTED"; }
        void RunPartTwo(std::ostream& outAnswer) override { outAnswer << "PART TWO NOT IMPLEMENTED"; }

        const std::vector<std::string>& GetInputLines() const { return m_inputLines; }
    };
}

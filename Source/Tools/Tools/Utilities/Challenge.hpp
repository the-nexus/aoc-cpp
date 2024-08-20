
#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Tools/Utilities/Factory.hpp"

namespace AOC::Tools
{
    class ChallengeID
    {
    public:
        constexpr ChallengeID(int const year, int const day)
            : m_year(year)
            , m_day(day)
        {}

        bool operator==(ChallengeID const& other) const
        {
            return m_year == other.m_year && m_day == other.m_day;
        }

        bool operator<(ChallengeID const& other) const
        {
            if (m_year == other.m_year)
            {
                return m_day < other.m_day;
            }
            return m_year < other.m_year;
        }

        constexpr int GetYear() const { return m_year; }
        constexpr int GetDay() const { return m_day; }

    private:
        int m_year = 0;
        int m_day = 0;
    };

    class IChallenge
    {
    public:
        virtual ~IChallenge() = default;
        virtual void RunPartOne() = 0;
        virtual void RunPartTwo() = 0;
    };

    template <int YearN, int DayN>
    class Challenge : public IChallenge
    {
    protected:
        static void __PART_NOT_IMPLEMENTED__(std::string const& name)
        {
            std::cout << "PART " << name << " NOT IMPLEMENTED" << std::endl;
        }

    public:
        static constexpr ChallengeID GetID() { return { YearN, DayN }; }

        Challenge(std::vector<std::string>&& inputLines)
            : m_inputLines(std::move(inputLines))
        {
            inputLines = {};
        }

        const std::vector<std::string>& GetInputLines() const { return m_inputLines; }

    private:
        std::vector<std::string> m_inputLines;
    };
}

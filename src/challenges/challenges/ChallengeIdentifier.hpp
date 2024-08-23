
#pragma once

namespace aoc::challenges
{
    class ChallengeIdentifier
    {
        int m_year = -1;
        int m_day = -1;

    public:
        constexpr ChallengeIdentifier(int const year, int const day)
            : m_year(year)
            , m_day(day)
        {}

        bool operator==(ChallengeIdentifier const& other) const
        {
            return m_year == other.m_year && m_day == other.m_day;
        }

        bool operator<(ChallengeIdentifier const& other) const
        {
            if (m_year == other.m_year)
            {
                return m_day < other.m_day;
            }
            return m_year < other.m_year;
        }

        constexpr int GetYear() const { return m_year; }
        constexpr int GetDay() const { return m_day; }
    };
}

#pragma once

namespace AOC::Tools
{
    struct ChallengeIdentifier
    {
        unsigned int m_year = 0;
        unsigned int m_day = 0;

        ChallengeIdentifier(unsigned int const year, unsigned int const day)
            : m_year(year)
            , m_day(day)
        {}

        bool operator==(ChallengeIdentifier const& other) const
        {
            return m_year == other.m_year && m_day == other.m_day;
        }
    };
}


#pragma once

#include "Tools/Utilities/Factory.hpp"

namespace AOC::Tools
{
    class ChallengeIdentifier
    {
    public:
        using ValueType = unsigned int;

        constexpr ChallengeIdentifier(ValueType const year, ValueType const day)
            : m_year(year)
            , m_day(day)
        {}

        bool operator==(ChallengeIdentifier const& other) const
        {
            return m_year == other.m_year && m_day == other.m_day;
        }

        constexpr ValueType GetYear() const { return m_year; }
        constexpr ValueType GetDay() const { return m_day; }

    private:
        ValueType m_year = 0;
        ValueType m_day = 0;
    };

    class Challenge
    {
    public:
        virtual ~Challenge() = default;
        virtual void RunPartOne() = 0;
        virtual void RunPartTwo() = 0;
    };

    class ChallengeFactory : public Factory<ChallengeIdentifier, Challenge> {};

    template <ChallengeIdentifier::ValueType YearN, ChallengeIdentifier::ValueType DayN>
    class ChallengeImpl
    {
    public:
        static constexpr ChallengeIdentifier sm_identifier = {YearN, DayN};
    };
}

#define REGISTER_CHALLENGE(__CHALLENGE_IMPL_TYPE__)                     \
    AOC::Tools::ChallengeFactory::Register(                             \
        __CHALLENGE_IMPL_TYPE__::sm_identifier,                         \
        []() { return std::make_unique<__CHALLENGE_IMPL_TYPE__>(); }    \
    );

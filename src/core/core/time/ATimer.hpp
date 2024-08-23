
#pragma once

#include <chrono>

namespace aoc::core
{
    class ATimer
    {
    protected:
        typedef std::chrono::high_resolution_clock Clock;
        typedef Clock::time_point TimeHandle;

    public:
        static TimeHandle GetTimeNow() { return Clock::now(); }
        static TimeHandle GetTimeZero() { return Clock::time_point(Clock::duration(0)); }

        virtual ~ATimer() = default;
        virtual float GetElapsedTime() const = 0;
    };
}

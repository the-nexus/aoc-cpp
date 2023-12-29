#pragma once

#include <chrono>

namespace TimeTool
{
    typedef std::chrono::high_resolution_clock Clock;
    typedef Clock::time_point TimeHandle;

    inline TimeHandle GetTimeNow() { return Clock::now(); }
    inline TimeHandle GetTimeZero() { return Clock::time_point(Clock::duration(0)); }

    struct PersistentTimer
    {
    public:
        PersistentTimer();

        inline void Start() { m_startTime = GetTimeNow(); }
        inline float GetElapsedTime() const { return std::chrono::duration_cast<std::chrono::microseconds>(GetTimeNow() - m_startTime).count() * 0.000001f; }

    private:
        TimeHandle m_startTime;
    };

    struct ChronoTimer
    {
    public:
        ChronoTimer();

        void Start();
        inline void Stop() { m_stopTime = GetTimeNow(); }
        inline float GetElapsedTime() const { return std::chrono::duration_cast<std::chrono::microseconds>((m_stopTime == m_startTime ? GetTimeNow() : m_stopTime) - m_startTime).count() * 0.000001f; }

    private:
        TimeHandle m_startTime;
        TimeHandle m_stopTime;
    };
}

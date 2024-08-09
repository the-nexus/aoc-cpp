
#include "ChronoTimer.h"

using namespace AOC::Tools;

ChronoTimer::ChronoTimer()
    : m_startTime(GetTimeZero())
    , m_stopTime(GetTimeZero())
{}

void ChronoTimer::Start()
{
    m_startTime = GetTimeNow();
    m_stopTime = m_startTime;
}

void ChronoTimer::Stop()
{
    m_stopTime = GetTimeNow();
}

float ChronoTimer::GetElapsedTime() const 
{
    float constexpr microsecondsToSeconds = 1.f / 1'000'000.f;
    return std::chrono::duration_cast<std::chrono::microseconds>((m_stopTime == m_startTime ? GetTimeNow() : m_stopTime) - m_startTime).count() * 0.000001f;
}


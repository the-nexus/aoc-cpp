
#include "PersistentTimer.h"

using namespace AOC::Tools;

PersistentTimer::PersistentTimer()
    : m_startTime(GetTimeNow())
{}

void PersistentTimer::Start()
{
    m_startTime = GetTimeNow();
}

float PersistentTimer::GetElapsedTime() const
{
    float constexpr microsecondsToSeconds = 1.f / 1'000'000.f;
    return std::chrono::duration_cast<std::chrono::microseconds>(GetTimeNow() - m_startTime).count() * microsecondsToSeconds;
}
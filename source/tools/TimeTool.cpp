#include "TimeTool.h"

namespace TimeTool
{
    PersistentTimer::PersistentTimer()
        : m_startTime(GetTimeNow())
    {}

    ChronoTimer::ChronoTimer()
        : m_startTime(GetTimeZero())
        , m_stopTime(GetTimeZero())
    {}

    void ChronoTimer::Start()
    {
        m_startTime = GetTimeNow();
        m_stopTime = m_startTime;
    }
}


#pragma once

#include "Tools/Time/ATimer.h"

namespace AOC::Tools
{
    class ChronoTimer final : public ATimer
    {
    public:
        ChronoTimer();

        void Start();
        void Stop() { m_stopTime = GetTimeNow(); }

        float GetElapsedTime() const override;

    private:
        TimeHandle m_startTime;
        TimeHandle m_stopTime;
    };
}

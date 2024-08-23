
#pragma once

#include "Tools/Time/ATimer.h"

namespace AOC::Tools
{
    class ChronoTimer final : public ATimer
    {
        TimeHandle m_startTime;
        TimeHandle m_stopTime;

    public:
        ChronoTimer();
        void Start();
        void Stop();
        float GetElapsedTime() const override;
    };
}

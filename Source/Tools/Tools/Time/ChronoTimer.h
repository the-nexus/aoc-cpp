
#pragma once

#include "Tools/Time/ATimer.h"

namespace AOC::Tools
{
    class ChronoTimer final : public ATimer
    {
    public:
        ChronoTimer();

        void Start();
        void Stop();

        float GetElapsedTime() const override;

    private:
        TimeHandle m_startTime;
        TimeHandle m_stopTime;
    };
}

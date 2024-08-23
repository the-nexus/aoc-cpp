
#pragma once

#include "core/time/ATimer.hpp"

namespace aoc::core
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

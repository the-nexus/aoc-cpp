
#pragma once

#include "core/time/ATimer.hpp"

namespace aoc::core
{
    class PersistentTimer final : public ATimer
    {
        TimeHandle m_startTime;

    public:
        PersistentTimer();
        void Start();
        float GetElapsedTime() const override;
    };
}

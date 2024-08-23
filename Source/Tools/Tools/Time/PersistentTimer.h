
#pragma once

#include "Tools/Time/ATimer.h"

namespace AOC::Tools
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

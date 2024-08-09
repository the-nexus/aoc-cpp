
#pragma once

#include "Tools/Time/ATimer.h"

namespace AOC::Tools
{
    class PersistentTimer final : public ATimer
    {
    public:
        PersistentTimer();
        void Start();

        float GetElapsedTime() const override;

    private:
        TimeHandle m_startTime;
    };
}

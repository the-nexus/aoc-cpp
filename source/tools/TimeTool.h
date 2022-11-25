
#include <chrono>

namespace TimeTool
{
    typedef std::chrono::high_resolution_clock::time_point TimeHandle;

    inline TimeHandle Now() { return std::chrono::high_resolution_clock::now(); }

    struct PersistentTimer
    {
    public:
        PersistentTimer();

        inline void Start() { m_start = Now(); }
        inline float GetElapsedTime() const { return std::chrono::duration_cast<std::chrono::microseconds>(Now() - m_start).count() * 0.000001f; }

    private:
        TimeHandle m_start;
    };
}

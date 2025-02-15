#include "Timing.h"

namespace GCrisp
{
    void Timer::ProcessTime(ProcessedTime& elapsed, const steady_clock::time_point& end)
    {
        elapsed.m_Time = duration_cast<nanoseconds>(end - m_Start).count() / 1000000000.0f;
        m_Start = end;
    }

    ScopedTimer::~ScopedTimer()
    {
        m_Elapsed = duration_cast<milliseconds>(steady_clock::now() - m_Start).count() / 1000.0f;
    }


    void TimingsProfiler::StartProfiler(const char* file)
    {
        auto iter = s_ProfilerMap.find(file);
        GC_CORE_VERIFY(iter == s_ProfilerMap.end(), "There is already a profiler started with filename {0}!", file);
    }

    void TimingsProfiler::EndProfiler()
    {
    }

    void TimingsProfiler::ProfileScope(const char* name)
    {
    }

    void TimingsProfiler::ProfileFunction()
    {
    }
}

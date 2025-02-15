#pragma once

#include <chrono>

namespace GCrisp
{
    using namespace std::chrono;


    class ProcessedTime
    {
        friend class Timer;

    public:
        ProcessedTime() : ProcessedTime(0.0f)
        {
        }

        ProcessedTime(float time) : m_Time(time)
        {
        }

        operator float() const { return m_Time; }

        inline float GetSeconds() const { return m_Time; }
        inline float GetMillis() const { return m_Time * 1000; }

    protected:
        float m_Time;
    };

    class Timer
    {
    public:
        Timer() : m_Start(steady_clock::now())
        {
        }

        void ProcessTime(ProcessedTime& elapsed, const steady_clock::time_point& end);

    private:
        steady_clock::time_point m_Start;
    };

    class ScopedTimer
    {
    public:
        ScopedTimer(steady_clock::time_point start, ProcessedTime& elapsed) : m_Elapsed(elapsed), m_Start(start)
        {
        }

        ~ScopedTimer();

    private:
        ProcessedTime& m_Elapsed;
        steady_clock::time_point m_Start;
    };

    class TimingsProfiler
    {
    public:
        static void StartProfiler(const char* file);
        static void EndProfiler();

        static void ProfileScope(const char* name);
        static void ProfileFunction();

    private:
        static std::unordered_map<const char*, std::vector<ProcessedTime>> s_ProfilerMap;
    };
}

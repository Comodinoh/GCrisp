#pragma once

#include <chrono>
#include <thread>

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
        inline double GetMicros() const { return m_Time * 1000000; }

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
        ScopedTimer(steady_clock::time_point& start, ProcessedTime& elapsed) : m_Elapsed(elapsed), m_Start(start){}

        virtual ~ScopedTimer();
    protected:
        ProcessedTime& m_Elapsed;
        steady_clock::time_point m_Start;
    };

    struct ProfileResult
    {
        const char* Name;
        std::thread::id Thread;
        ProcessedTime Elapsed = ProcessedTime();
        steady_clock::time_point Start = steady_clock::now();
    };

    class ProfilerTimer : public ScopedTimer
    {
    public:
        ProfilerTimer(ProfileResult& result) : ScopedTimer(result.Start, result.Elapsed), m_Result(result)
        {
        }

        virtual ~ProfilerTimer() override;
    private:
        ProfileResult& m_Result;
    };


    class TimingsProfiler
    {
    public:
        static void Init();
        static void Shutdown();

        static void StartProfiler(const char* file);
        static void EndProfiler();

        static void AddProfileResult(ProfileResult& result);
    private:
        static std::unordered_map<std::string, std::vector<ProfileResult>> s_ProfilerMap;
        static char* s_CurrentProfiler;
    };
}

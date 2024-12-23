#pragma once


namespace GCrisp{

using namespace std::chrono;


class ProcessedTime
{
friend class Timer;
public:
  ProcessedTime() : ProcessedTime(0.0f) {}
  ProcessedTime(float time) : m_Time(time) {}

  operator float() const {return m_Time;}

  inline float GetSeconds() const {return m_Time;}
  inline float GetMillis() const {return m_Time*1000;}
protected:
  float m_Time;
};

class Timer
{
public:
  Timer() : m_Last(steady_clock::now()) {}
 
  void ProcessTime(ProcessedTime& elapsed, const steady_clock::time_point& now);
private:
  steady_clock::time_point m_Last;     
};

class ScopedTimer
{
public:
  ScopedTimer(steady_clock::time_point start, ProcessedTime& elapsed) : m_Start(start), m_Elapsed(elapsed) {}
  ~ScopedTimer();
private:
  ProcessedTime& m_Elapsed;
  steady_clock::time_point m_Start;
};

}

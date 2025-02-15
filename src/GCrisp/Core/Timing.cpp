#include "Timing.h"

namespace GCrisp{

void Timer::ProcessTime(ProcessedTime& elapsed, const steady_clock::time_point& now)
{
  elapsed.m_Time = duration_cast<nanoseconds>(now-m_Last).count()/1000000000.0f;
  m_Last = now;
}

ScopedTimer::~ScopedTimer()
{
  m_Elapsed = duration_cast<milliseconds>(steady_clock::now()-m_Start).count()/1000.0f;
}

}



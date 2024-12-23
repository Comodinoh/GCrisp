#include "Timer.h"
#include <GCrisp/Core/PlatformUtils.h>
#include <GLFW/glfw3.h>

namespace GCrisp{

void Timer::processTime(int64_t now)
{
  m_Elapsed.m_Time = now-m_Last;
  m_Last = now;
}

ScopedTimer::~ScopedTimer()
{
  m_Elapsed = PlatformUtils::GetTime()-m_Start;
}

}



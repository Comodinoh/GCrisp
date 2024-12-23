#include <GCrisp/Core/PlatformUtils.h>
#include <Windows.h>

namespace GCrisp{

namespace PlatformUtils{


// Note: Untested and maybe unstable
int64_t GetTime()
{
  LARGE_INTEGER time;

  QueryPerformanceCounter(&time);

  return time;

}

}

}

#include <GCrisp/Core/PlatformUtils.h>
#include <time.h>

namespace GCrisp{

namespace PlatformUtils{

int64_t GetTime()
{
  timespec spec;

  clock_gettime(CLOCK_MONOTONIC_RAW, &spec);

  // divide the nanoseconds with a billion to obtain seconds in float
  return (int64_t)spec.tv_sec * 1e9 + spec.tv_nsec;
}

}

}

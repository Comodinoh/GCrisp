#pragma once

#define ENGINE_NAME "GCrisp"

#include <memory>

#ifndef GC_RELEASE
#if defined(GC_WIN32)
#define GC_BREAKPOINT() __debugbreak()
#elif defined(GC_POSIX)
    #include <signal.h>
    #define GC_BREAKPOINT() raise(SIGTRAP)
#else
    #error "Platform doesn't support debugbreak!"
#endif
#define GC_ASSERT(condition, ...) if(!(condition)) {GC_ERROR("Assertion Failed: {0}", __VA_ARGS__); GC_BREAKPOINT();}
#define GC_CORE_ASSERT(condition, ...) if(!(condition)) {GC_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); GC_BREAKPOINT();}
#else
  #define GC_ASSERT(condition, ...)
  #define GC_CORE_ASSERT(condition, ...)
#endif

#ifndef GC_DIST
#define GC_VERIFY(condition, msg, ...) {if(!(condition)) GC_ERROR(msg, __VA_ARGS__);}
#define GC_CORE_VERIFY(condition, msg, ...) {if(!(condition)) GC_CORE_ERROR(msg, __VA_ARGS__);}
#else
  #define GC_VERIFY(condition, msg, ...)
  #define GC_CORE_VERIFY(condition, msg, ...)
#endif

#define BIT(x) (1 << x)
#define GC_BIND_FN1(func) std::bind(&func, this, std::placeholders::_1)

namespace GCrisp
{
  template <typename T>
  using Reference = std::shared_ptr<T>;

  template <typename T>
  using ScopedPtr = std::unique_ptr<T>;
}


#pragma once

#define ENGINE_NAME "GCrisp"


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

#define GC_VERIFY(x, msg, ...) {if(!(x)) GC_ERROR(msg, __VA_ARGS__);}
#define GC_CORE_VERIFY(x, msg, ...) {if(!(x)) GC_CORE_ERROR(msg, __VA_ARGS__);}

#define BIT(x) (1 << x)

#include <GCrisp/Core/Log.h>



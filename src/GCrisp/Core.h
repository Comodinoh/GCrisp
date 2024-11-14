#pragma once

#define ENGINE_NAME "GCrisp"

#ifdef _GCRISP_DEBUG
  #define GC_ASSERT(x, ...) {if(!(x)) {GC_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
  #define GC_CORE_ASSERT(x, ...) {if(!(x)) {GC_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
#else
  #define GC_ASSERT(x, ...)
  #define GC_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)



#pragma once

#define ENGINE_NAME "GCrisp"

#ifndef GC_RELEASE
  #define GC_ASSERT(x){assert(x);}
#else
  #define GC_ASSERT(x)
#endif

#define BIT(x) (1 << x)



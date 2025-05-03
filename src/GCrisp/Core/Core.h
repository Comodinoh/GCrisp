#pragma once

#define ENGINE_NAME "GCrisp"

#include <memory>

#define BIT(x)			  (1 << x)
#define GC_BIND_FN1(func) std::bind(&func, this, std::placeholders::_1)
#define GC_CONCAT(x, y)	  x##y

#ifndef GC_RELEASE

#if defined(GC_WIN32)
#define GC_BREAKPOINT() __debugbreak()
#elif defined(GC_POSIX)
#include <signal.h>
#define GC_BREAKPOINT() raise(SIGTRAP)
#else
#error "Platform doesn't support debugbreak!"
#endif

#define GC_ASSERT(condition, ...)                       \
	if (!(condition)) {                                 \
		GC_ERROR("Assertion Failed: {0}", __VA_ARGS__); \
		GC_BREAKPOINT();                                \
	}

#define GC_CORE_ASSERT(condition, ...)                       \
	if (!(condition)) {                                      \
		GC_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); \
		GC_BREAKPOINT();                                     \
	}

#else

#define GC_ASSERT(condition, ...)
#define GC_CORE_ASSERT(condition, ...)

#endif

#ifndef GC_DIST

#define GC_VERIFY(condition, msg, ...) \
	if (!(condition)) {                \
		GC_ERROR(msg, __VA_ARGS__);    \
	}

#define GC_CORE_VERIFY(condition, msg, ...) \
	if (!(condition)) {                     \
		GC_CORE_ERROR(msg, __VA_ARGS__);    \
	}

#else

#define GC_VERIFY(condition, msg, ...)
#define GC_CORE_VERIFY(condition, msg, ...)

#endif

// Note: This is currently way too slow to use for
// true profiling purposes, to be remade.
#define GC_PROFILING 0
#if GC_PROFILING

#ifndef __JETBRAINS_IDE__

#define GC_PROFILE_START(name) ::GCrisp::TimingsProfiler::StartProfiler(name);
#define GC_PROFILE_END()	   ::GCrisp::TimingsProfiler::EndProfiler();

#define GC_PROFILE_SCOPE2(name, line)                                               \
	ProfileResult			GC_CONCAT(result, line) = {name,                        \
													   std::this_thread::get_id()}; \
	::GCrisp::ProfilerTimer GC_CONCAT(timer, line)(GC_CONCAT(result, line));

#define GC_PROFILE_SCOPE(name) GC_PROFILE_SCOPE2(name, __LINE__)

#if defined(_MSC_VER) && !defined(__llvm__) && !defined(__GNUC__) && \
	!defined(__clang__)

#define GC_PROFILE_FUNC() GC_PROFILE_SCOPE(__FUNCSIG__)

#else

#define GC_PROFILE_FUNC() GC_PROFILE_SCOPE(__PRETTY_FUNCTION__)

#endif

#else

#define GC_PROFILE_START(1)
#define GC_PROFILE_END()
#define GC_PROFILE_SCOPE2(1, 2)
#define GC_PROFILE_SCOPE(1)
#define GC_PROFILE_FUNC() GC_PROFILE_SCOPE(__PRETTY_FUNCTION__)

#endif

#else

#define GC_PROFILE_START(name)
#define GC_PROFILE_END()
#define GC_PROFILE_SCOPE2(name, line)
#define GC_PROFILE_SCOPE(name)
#define GC_PROFILE_FUNC() GC_PROFILE_SCOPE(__PRETTY_FUNCTION__)

#endif

namespace GCrisp
{
template <typename T> using Reference = std::shared_ptr<T>;

template <typename T> using ScopedPtr = std::unique_ptr<T>;
} // namespace GCrisp

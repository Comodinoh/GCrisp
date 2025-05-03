#pragma once

#include <GCrisp/Core/Core.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/spdlog.h>

namespace GCrisp
{
class Log
{
  public:
	static void									   Init();
	inline static std::shared_ptr<spdlog::logger>& GetCoreLogger()
	{
		return s_CoreLogger;
	}
	inline static std::shared_ptr<spdlog::logger>& GetClientLogger()
	{
		return s_ClientLogger;
	}

  private:
	static std::shared_ptr<spdlog::logger> s_CoreLogger;
	static std::shared_ptr<spdlog::logger> s_ClientLogger;
};
}; // namespace GCrisp

// Core log macros
#define GC_CORE_FATAL(...) ::GCrisp::Log::GetCoreLogger()->fatal(__VA_ARGS__)
#define GC_CORE_ERROR(...) ::GCrisp::Log::GetCoreLogger()->error(__VA_ARGS__)
#define GC_CORE_WARN(...)  ::GCrisp::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define GC_CORE_INFO(...)  ::GCrisp::Log::GetCoreLogger()->info(__VA_ARGS__)
#define GC_CORE_TRACE(...) ::GCrisp::Log::GetCoreLogger()->trace(__VA_ARGS__)

// App log macros
#define GC_ERROR(...) ::GCrisp::Log::GetClientLogger()->error(__VA_ARGS__)
#define GC_WARN(...)  ::GCrisp::Log::GetClientLogger()->warn(__VA_ARGS__)
#define GC_INFO(...)  ::GCrisp::Log::GetClientLogger()->info(__VA_ARGS__)
#define GC_TRACE(...) ::GCrisp::Log::GetClientLogger()->trace(__VA_ARGS__)

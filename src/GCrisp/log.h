#pragma once
#include <memory>
#include <spdlog/spdlog.h>
#include <GCrisp/core.h>

namespace gcrisp {

class Log
{
public:
  static void Init();
  inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
  inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

private:
  static std::shared_ptr<spdlog::logger> s_CoreLogger;
  static std::shared_ptr<spdlog::logger> s_ClientLogger;
};

};

// Core log macros
#define GC_CORE_FATAL(...)   ::gcrisp::Log::GetCoreLogger()->fatal(__VA__ARGS__)
#define GC_CORE_ERROR(...)   ::gcrisp::Log::GetCoreLogger()->error(__VA__ARGS__)
#define GC_CORE_WARN(...)    ::gcrisp::Log::GetCoreLogger()->warn(__VA__ARGS__)
#define GC_CORE_INFO(...)    ::gcrisp::Log::GetCoreLogger()->info(__VA__ARGS__)
#define GC_CORE_TRACE(...)   ::gcrisp::Log::GetCoreLogger()->trace(__VA__ARGS__)

#define GC_ERROR(...)        ::gcrisp::Log::GetClientLogger()->error(__VA__ARGS__)
#define GC_WARN(...)         ::gcrisp::Log::GetClientLogger()->warn(__VA__ARGS__)
#define GC_INFO(...)         ::gcrisp::Log::GetClientLogger()->info(__VA__ARGS__)
#define GC_TRACE(...)        ::gcrisp::Log::GetClientLogger()->trace(__VA__ARGS__)
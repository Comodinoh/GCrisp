#include "Log.h"
#include <gcpch.h>

#include <spdlog/sinks/stdout_color_sinks.h>

namespace GCrisp {
std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

void Log::Init() {
    spdlog::set_pattern("%^[%T] %n: %v%$");
    s_CoreLogger = spdlog::stdout_color_mt(ENGINE_NAME);
    s_CoreLogger->set_level(spdlog::level::trace);

    s_ClientLogger = spdlog::stdout_color_mt("App");
    s_ClientLogger->set_level(spdlog::level::trace);
}

void Log::Shutdown() {
    spdlog::shutdown();

    s_CoreLogger.reset();
    s_ClientLogger.reset();
}
}; // namespace GCrisp

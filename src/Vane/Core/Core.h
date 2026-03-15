#pragma once

namespace Vane
{
class Core
{
public:
    static void Init()
    {
        Vane::Log::Init();
        Vane::Log::GetCoreLogger()->info("Initialized Logger!");

        Vane::TimingsProfiler::Init();
    }

    static void Shutdown()
    {
        Vane::TimingsProfiler::Shutdown();

        Vane::Log::Shutdown();
    }

    static bool IsRunning() { return s_Running; }
    static void SetRunning(bool value) { s_Running = value; }

private:
    static bool s_Running;
};
}
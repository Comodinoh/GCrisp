#pragma once

namespace GCrisp {
class Core {
public:
    static void Init() {
        GCrisp::Log::Init();
        GCrisp::Log::GetCoreLogger()->info("Initialized Logger!");
        GCrisp::TimingsProfiler::Init();
    }

    static void Shutdown() {
        GCrisp::TimingsProfiler::Shutdown();
        GCrisp::Log::Shutdown();
    }

    static bool IsRunning() { return s_Running; }
    static void SetRunning(bool value) { s_Running = value; }

private:
    static bool s_Running;
};
}
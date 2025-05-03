#pragma once
#include <GCrisp/Core/Core.h>

extern GCrisp::Application* GCrisp::CreateApplication();

int main(int argc, char** argv)
{
	GCrisp::Log::Init();
	GCrisp::Log::GetCoreLogger()->info("Initialized Logger!");
	GCrisp::TimingsProfiler::Init();

	GC_PROFILE_START("GCrispStart");
	auto app = GCrisp::CreateApplication();
	GC_PROFILE_END();

	GC_PROFILE_START("GCrispRuntime");
	app->Run();
	GC_PROFILE_END();

	GC_PROFILE_START("GCrispShutdown");
	delete app;
	GC_PROFILE_END();

	GCrisp::TimingsProfiler::Shutdown();
}

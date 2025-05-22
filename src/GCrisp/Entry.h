#pragma once
#include "Core/Memory/Allocator.h"
#include "GCrisp/Core/Base.h"
#include "GCrisp/Core/Core.h"

extern GCrisp::Application* GCrisp::CreateApplication();

int main(int argc, char** argv)
{
    GCrisp::Memory::g_GlobalAllocator = new GCrisp::Memory::Allocator();

    while (GCrisp::Core::IsRunning()) {
        GCrisp::Core::Init();

        GC_PROFILE_START("GCrispStart");
        auto app = GCrisp::CreateApplication();
        GC_PROFILE_END();

        // GC_CORE_TRACE("Allocated {0}",
        //               GCrisp::Memory::GetGlobalAllocator()->GetStatistics()->
        //               Allocated);

        GC_PROFILE_START("GCrispRuntime");
        app->Run();
        GC_PROFILE_END();

        GC_PROFILE_START("GCrispShutdown");
        delete app;
        GC_PROFILE_END();

        GCrisp::Core::Shutdown();
    }

    delete GCrisp::Memory::g_GlobalAllocator;

}

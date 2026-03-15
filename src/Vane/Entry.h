#pragma once
#include "Core/Memory/Allocator.h"
#include "Vane/Core/Base.h"
#include "Vane/Core/Core.h"

extern Vane::Application* Vane::CreateApplication();

int main(int argc, char** argv)
{
    Vane::Memory::g_GlobalAllocator = new Vane::Memory::Allocator();

    while (Vane::Core::IsRunning()) {
        Vane::Core::Init();

        VANE_PROFILE_START("VaneStart");
        auto app = Vane::CreateApplication();
        VANE_PROFILE_END();

        // VANE_CORE_TRACE("Allocated {0}",
        //               Vane::Memory::GetGlobalAllocator()->GetStatistics()->
        //               Allocated);

        VANE_PROFILE_START("VaneRuntime");
        app->Run();
        VANE_PROFILE_END();

        VANE_PROFILE_START("VaneShutdown");
        delete app;
        VANE_PROFILE_END();

        Vane::Core::Shutdown();
    }

    delete Vane::Memory::g_GlobalAllocator;

}

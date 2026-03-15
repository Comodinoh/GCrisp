set(VANE_LINUX_SOURCE
    Vane/Platform/LinuxWindowCreator.cpp
)

target_sources(Vane-Platform INTERFACE ${VANE_LINUX_SOURCE})

target_compile_definitions(Vane-Platform INTERFACE
    VANE_POSIX
)

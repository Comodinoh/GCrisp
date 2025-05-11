set(GCRISP_LINUX_SOURCE
    GCrisp/Platform/LinuxWindowCreator.cpp
)

target_sources(GCrisp-Platform INTERFACE ${GCRISP_LINUX_SOURCE})

target_compile_definitions(GCrisp-Platform INTERFACE
    GC_POSIX
)

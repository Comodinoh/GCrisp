add_subdirectory(Commons)

if(VANE_WIN32)
    add_subdirectory(Win32)
elseif(VANE_POSIX)
    add_subdirectory(Linux)
endif()

add_subdirectory(Commons)

if(GCRISP_WIN32)
    add_subdirectory(Win32)
elseif(GCRISP_POSIX)
    add_subdirectory(Linux)
endif()

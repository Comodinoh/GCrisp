add_library(Vane-OpenGL INTERFACE)

set(GCRISP_OPENGL_SOURCES 
    Vane/Platform/OpenGL/GGLAPI.h
    Vane/Platform/OpenGL/GLBuffer.h
    Vane/Platform/OpenGL/GLContext.h
    Vane/Platform/OpenGL/GLShader.h
    Vane/Platform/OpenGL/GLTexture.h
    Vane/Platform/OpenGL/GLVertexArray.h
    Vane/Platform/OpenGL/GLWindow.h
    Vane/Platform/OpenGL/GGLAPI.cpp
    Vane/Platform/OpenGL/GLBuffer.cpp
    Vane/Platform/OpenGL/GLContext.cpp
    Vane/Platform/OpenGL/GLShader.cpp
    Vane/Platform/OpenGL/GLTexture.cpp
    Vane/Platform/OpenGL/GLVertexArray.cpp
    Vane/Platform/OpenGL/GLWindow.cpp
)

target_sources(Vane-OpenGL INTERFACE ${GCRISP_OPENGL_SOURCES})

target_include_directories(Vane-OpenGL INTERFACE .)

add_library(GCrisp-OpenGL INTERFACE)

set(GCRISP_OPENGL_SOURCES 
    GCrisp/Platform/OpenGL/GGLAPI.h
    GCrisp/Platform/OpenGL/GLBuffer.h
    GCrisp/Platform/OpenGL/GLContext.h
    GCrisp/Platform/OpenGL/GLShader.h
    GCrisp/Platform/OpenGL/GLTexture.h
    GCrisp/Platform/OpenGL/GLVertexArray.h
    GCrisp/Platform/OpenGL/GLWindow.h
    GCrisp/Platform/OpenGL/GGLAPI.cpp
    GCrisp/Platform/OpenGL/GLBuffer.cpp
    GCrisp/Platform/OpenGL/GLContext.cpp
    GCrisp/Platform/OpenGL/GLShader.cpp
    GCrisp/Platform/OpenGL/GLTexture.cpp
    GCrisp/Platform/OpenGL/GLVertexArray.cpp
    GCrisp/Platform/OpenGL/GLWindow.cpp
)

target_sources(GCrisp-OpenGL INTERFACE ${GCRISP_OPENGL_SOURCES})

target_include_directories(GCrisp-OpenGL INTERFACE .)

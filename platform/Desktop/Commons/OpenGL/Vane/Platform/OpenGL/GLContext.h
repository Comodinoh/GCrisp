#pragma once

#include <Vane/Core/Base.h>
#include <Vane/Renderer/Context.h>
#include <GLFW/glfw3.h>

namespace Vane {
namespace Graphics {
struct GLContextSpecification {
    GLFWwindow* WindowHandle;
};

class GLContext : public Context {
  public:
    GLContext(const ContextSpecification& spec)
        : m_Spec((GLFWwindow*)spec.WindowHandle) {
        VANE_CORE_ASSERT(spec.WindowHandle,
                       "Provided invalid window handle! (nullptr)");
    };

    virtual void Init() const override;
    virtual void SwapBuffers() const override;

  private:
    GLContextSpecification m_Spec;
};
} // namespace Graphics
} // namespace Vane

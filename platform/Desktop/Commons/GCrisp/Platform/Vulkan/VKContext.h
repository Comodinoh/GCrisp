#pragma once

#include <GCrisp/Renderer/Context.h>
#include <vulkan/vulkan.h>

struct GLFWwindow;

namespace GCrisp
{
namespace Graphics
{

class VKContext : public Context
{
  public:
	VKContext(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle)
	{
		GC_CORE_ASSERT(windowHandle,
					   "Provided invalid window handle! (nullptr)");
	}

	virtual void Init() const override;

	virtual void SwapBuffers() const override;

  private:
	GLFWwindow* m_WindowHandle;
};

} // namespace Graphics
} // namespace GCrisp

#pragma once

#include <GCrisp/Core/GWindow.h>
#include <vulkan/vulkan.hpp>

struct GLFWwindow;

namespace GCrisp{

    // TODO: Implement vulkan window backend

    class VKWindow : Window
    {
    public:
        VKWindow(const Graphics::Backend& backend, const WindowProps& props);
        virtual ~VKWindow();

        virtual void OnUpdate() override;
        virtual void TransferContext() override;

        inline virtual void* GetWindowPointer() override { return m_Window; };
        inline virtual Graphics::Context* GetContext() override { return m_Context; };

        virtual void SetResizable(bool enabled) override;

        virtual void SetVSync(bool enabled) override;

        static VkInstance& GetVulkan() {return m_VulkanInstance;};

    protected:
        GLFWwindow* m_Window;
        Graphics::Context* m_Context;

        static VkInstance m_VulkanInstance;

        virtual void Init(const WindowProps& props);
        virtual void Shutdown();
    };


}

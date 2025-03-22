#pragma once

#include <GCrisp/Core/GWindow.h>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace GCrisp{

    // TODO: Implement vulkan window backend

    struct VKData
    {
        VkPhysicalDevice SelectedDevice;
    };

    class VKWindow : Window
    {
    public:
        VKWindow(const Graphics::Backend& backend, const WindowProps& props);
        virtual ~VKWindow() override;

        virtual void OnUpdate() override;
        virtual void TransferContext() override;

        inline virtual void* GetWindowPointer() override { return m_Window; };
        inline virtual Graphics::Context* GetContext() override { return m_Context; };

        virtual void SetResizable(bool enabled) override;

        virtual void SetVSync(bool enabled) override;
         
        static VkInstance& GetVulkan() {return s_VulkanInstance;};
        static VKData& GetVulkanData() {return s_VulkanData;};


    protected:
        GLFWwindow* m_Window;
        Graphics::Context* m_Context;

        static VkInstance s_VulkanInstance;
        static VKData s_VulkanData;

        virtual void Init(const WindowProps& props);
        virtual void Shutdown();
    };


}

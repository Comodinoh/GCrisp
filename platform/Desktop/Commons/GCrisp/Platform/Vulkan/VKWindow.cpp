#include "VKWindow.h"
#include <gcpch.h>

#include <GCrisp/Events/ApplicationEvent.h>
#include <GCrisp/Events/KeyEvent.h>
#include <GCrisp/Events/MouseEvent.h>

#include "VKContext.h"
#include "VKUtils.h"

namespace GCrisp {
static bool s_GLFWInitialized = false;

VkInstance VKWindow::s_VulkanInstance = nullptr;
VKData VKWindow::s_VulkanData = {};

static void GLFWErrorCallback(int error, const char* desc) {
    GC_CORE_ERROR("GLFW Error: {0}: {1}", error, desc);
}

void VKWindow::Init() {
    GC_PROFILE_FUNC();

    WindowData& data = m_Spec.Data;

    GC_CORE_INFO("Creating GLFW window {0} ({1}, {2})", data.Title, data.Width,
                 data.Height);

    if (!s_GLFWInitialized) {
        GC_PROFILE_SCOPE("glfwInit - OpenVKWindow");
        int success = glfwInit();
        GC_CORE_ASSERT(success, "Could not initialize GLFW!");

        glfwSetErrorCallback(GLFWErrorCallback);

        s_GLFWInitialized = true;
    }

    glfwWindowHint(GLFW_RESIZABLE, data.Resizable);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    {
        GC_PROFILE_SCOPE("glfwCreateWindow - OpenVKWindow");
        m_Window = glfwCreateWindow((int)data.Width, (int)data.Height,
                                    data.Title.c_str(), nullptr, nullptr);
    }

    VkApplicationInfo appInfo = {
        .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .pApplicationName = data.Title.c_str(),
        .applicationVersion = VK_MAKE_API_VERSION(1, 1, 0, 0),
        .pEngineName = ENGINE_NAME,
        .engineVersion = VK_MAKE_API_VERSION(1, 1, 0, 0),
        .apiVersion = VK_API_VERSION_1_3};

    uint32_t glfwExtCount;
    const char** glfwExt = glfwGetRequiredInstanceExtensions(&glfwExtCount);

    VkInstanceCreateInfo info = {
        .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .pApplicationInfo = &appInfo,
        .enabledLayerCount = 0,
        .ppEnabledLayerNames = nullptr,
        .enabledExtensionCount = glfwExtCount,
        .ppEnabledExtensionNames = glfwExt,
    };

    uint32_t extCount = 0;

    vkEnumerateInstanceExtensionProperties(nullptr, &extCount, nullptr);

    VkExtensionProperties* exts =
        (VkExtensionProperties*)calloc(extCount, sizeof(VkExtensionProperties));

    vkEnumerateInstanceExtensionProperties(nullptr, &extCount, exts);

    // May get VK_ERROR_INCOMPATIBLE_DRIVER on MacOS with latest MoltenVK sdk
    GC_CORE_VERIFY(vkCreateInstance(&info, nullptr, &s_VulkanInstance) ==
                       VK_SUCCESS,
                   "Failed to create Vulkan instance!", nullptr);

    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(s_VulkanInstance, &deviceCount, nullptr);

    VkPhysicalDevice* devices =
        (VkPhysicalDevice*)calloc(deviceCount, sizeof(VkPhysicalDevice));
    vkEnumeratePhysicalDevices(s_VulkanInstance, &deviceCount, devices);

    VkPhysicalDeviceProperties deviceProperties;

    uint32_t n = 0;
    uint32_t selected = 0;

    VkPhysicalDevice device = nullptr;

    for (uint32_t i = 0; i < deviceCount; i++) {
        vkGetPhysicalDeviceProperties(devices[i], &deviceProperties);

        if (deviceProperties.deviceType ==
            VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
            device = devices[i];
            break;
        }

        // TODO: How do you even get the texture bound limit?!
        // TODO: Pick the device based on a score
    }

    if (!device) {
        GC_CORE_ERROR(
            "Couldn't find a compatible discrete graphic card for Vulkan.");
        return;
    }

    s_VulkanData.SelectedDevice = device;

    std::string_view name = deviceProperties.deviceName;

    std::string_view vendor;
    Utils::GetVendorName(deviceProperties.vendorID, &vendor);

    m_GraphicsSpec.Renderer = name;
    m_GraphicsSpec.Vendor = vendor;

    uint32_t apiVer = deviceProperties.apiVersion;

    Version apiVersion = {
        VK_API_VERSION_VARIANT(apiVer), VK_API_VERSION_MAJOR(apiVer),
        VK_API_VERSION_MINOR(apiVer), VK_API_VERSION_PATCH(apiVer)};

    GC_CORE_INFO("Vulkan Specifications:");
    GC_CORE_INFO("   Vendor: {0}", m_GraphicsSpec.Vendor);
    GC_CORE_INFO("   Renderer: {0}", m_GraphicsSpec.Renderer);
    GC_CORE_INFO("   Vulkan Version: {0}", m_GraphicsSpec.APIVersion.GetName());
    GC_CORE_INFO("   SL Version: {0}", m_GraphicsSpec.SLVersion);

    m_Context = new Graphics::VKContext(m_Window);
    m_Context->Init();

    int textureSlots = 0;
    // m_GraphicsSpec = GraphicsSpec{(char*)glGetString(GL_RENDERER),
    //     (char*)glGetString(GL_VENDOR),
    //     (char*)glGetString(GL_VERSION),
    //     (char*)glGetString(GL_SHADING_LANGUAGE_VERSION),
    //     (uint32_t)textureSlots};

    glfwSetWindowUserPointer(m_Window, &m_Spec.Data);
    SetVSync(data.VSync);

    // Set up GLFW callbacks
    glfwSetWindowSizeCallback(
        m_Window, [](GLFWwindow* window, int width, int height) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            WindowResizeEvent event(width, height);
            data.Width = width;
            data.Height = height;
            data.EventCallback(event);
        });

    glfwSetWindowIconifyCallback(
        m_Window, [](GLFWwindow* window, int iconified) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            WindowMinimizeEvent event(iconified == GLFW_TRUE);
            data.EventCallback(event);
        });

    glfwSetWindowFocusCallback(m_Window, [](GLFWwindow* window, int focused) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        WindowFocusEvent event(focused == GLFW_TRUE);
        data.EventCallback(event);
    });

    glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        WindowCloseEvent event;
        data.EventCallback(event);
    });

    glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode,
                                    int action, int mods) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

        switch (action) {
        case GLFW_PRESS: {
            KeyPressedEvent event(key, 0);
            data.EventCallback(event);
            break;
        }
        case GLFW_RELEASE: {
            KeyReleasedEvent event(key);
            data.EventCallback(event);
            break;
        }
        // This case is usually never reached in newer GLFW versions and
        // it's generally better to never use it
        case GLFW_REPEAT: {
            KeyPressedEvent event(key, 1);
            data.EventCallback(event);
            break;
        }
        }
    });

    glfwSetMouseButtonCallback(
        m_Window, [](GLFWwindow* window, int button, int action, int mods) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action) {
            case GLFW_PRESS: {
                MouseButtonPressedEvent event(button);
                data.EventCallback(event);
                break;
            }
            case GLFW_RELEASE: {
                MouseButtonReleasedEvent event(button);
                data.EventCallback(event);
                break;
            }
            }
        });

    glfwSetScrollCallback(
        m_Window, [](GLFWwindow* window, double xOff, double yOff) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseScrolledEvent event((float)xOff, (float)yOff);
            data.EventCallback(event);
        });

    glfwSetCursorPosCallback(
        m_Window, [](GLFWwindow* window, double xPos, double yPos) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseMovedEvent event((float)xPos, (float)yPos);
            data.EventCallback(event);
        });
}

void VKWindow::Shutdown() {
    GC_PROFILE_FUNC();
    glfwDestroyWindow(m_Window);
}

void VKWindow::OnUpdate() {
    GC_PROFILE_FUNC();
    glfwPollEvents();
    m_Context->SwapBuffers();
}

void VKWindow::TransferContext() { glfwMakeContextCurrent(m_Window); }

void VKWindow::SetResizable(bool enabled) {
    GC_PROFILE_FUNC();
    glfwWindowHint(GLFW_RESIZABLE, enabled ? GLFW_TRUE : GLFW_FALSE);
    m_Spec.Data.Resizable = enabled;
}

void VKWindow::SetVSync(bool enabled) {
    GC_PROFILE_FUNC();
    if (enabled) {
        glfwSwapInterval(1);
    } else {
        glfwSwapInterval(0);
    }

    m_Spec.Data.VSync = enabled;
}
} // namespace GCrisp

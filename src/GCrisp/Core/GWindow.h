#pragma once

#include <GCrisp/Renderer/Creator.h>
#include <GCrisp/Renderer/Renderer.h>
#include <GCrisp/Core/Core.h>
#include <GCrisp/Events/Event.h>
#include <GCrisp/Renderer/Context.h>

namespace GCrisp
{
    using EventCallbackFunc = std::function<void(Event&)>;

    struct Version
    {
        Version(const uint32_t variant = 0, const uint32_t major = 1, const uint32_t minor = 0, const uint32_t patch = 0)
        {
            Variant = variant;
            Major = major;
            Minor = minor;
            Patch = patch;
        }

        std::string_view GetName() const
        {
            const size_t len = 256;
            char buf[len];
            snprintf(buf, len, "%d-%d.%d.%d", Variant, Major, Minor, Patch);

            return buf;
        }

        std::string_view GetNameNoVariant()
        {
            const size_t len = 256;
            char buf[len];
            snprintf(buf, len, "%d.%d.%d", Major, Minor, Patch);

            return buf;
        }

        uint32_t Variant;
        uint32_t Major;
        uint32_t Minor;
        uint32_t Patch;
    };

    struct GraphicsSpec
    {
        std::string_view Renderer;
        std::string_view Vendor;
        std::string_view SLVersion; 

        Version APIVersion;

        uint32_t TextureSlots;

        // Usually used only with Vulkan, otherwise it's going to be a nullptr
        std::string_view* ExtensionNames = nullptr;
        uint32_t ExtensionCount = 0;

        std::string_view SelectedDevice;
        uint32_t PhysicalDeviceCount = 0;
    };

    struct WindowData
    {
        std::string Title;
        uint32_t Width, Height;
        bool VSync;
        bool Resizable;

        EventCallbackFunc EventCallback;
    };

    struct WindowProps
    {
        std::string Title;
        uint32_t Width, Height;
        bool Resizable;

        WindowProps(const std::string& title = ENGINE_NAME,
                    uint32_t width = 1280,
                    uint32_t height = 720, bool resizable = true) : Title(title), Width(width), Height(height),
                                                                    Resizable(resizable)
        {
        }
    };

    class Window
    {
    public:
        Window(const Graphics::Backend& backend) : m_Backend(backend)
        {
        }

        virtual ~Window() = default;

        virtual void OnUpdate() = 0;
        virtual void TransferContext() = 0;

        inline Graphics::Creator* GetCreator() const { return m_GraphicsCreator; }
        inline Graphics::Backend GetBackend() { return m_Backend; }
        inline uint32_t GetWidth() const { return m_Data.Width; }
        inline uint32_t GetHeight() const { return m_Data.Height; }
        inline GraphicsSpec GetGraphicsSpec() const {return m_GraphicsSpec;}

        virtual void SetResizable(bool enabled) = 0;
        inline bool IsResizable() const { return m_Data.Resizable; }


        inline virtual void* GetWindowPointer() = 0;
        inline virtual Graphics::Context* GetContext() = 0;

        virtual void SetVSync(bool enabled) = 0; 
        inline bool HasVSync() const { return m_Data.VSync; }

        void SetEventCallback(const EventCallbackFunc& callback) { m_Data.EventCallback = callback; };

        static Window* Create(const Graphics::Backend& backend, const WindowProps& props = WindowProps());

    protected:
        WindowData m_Data;
        Graphics::Backend m_Backend;
        Graphics::Creator* m_GraphicsCreator;
        GraphicsSpec m_GraphicsSpec;
    };
}

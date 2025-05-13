#pragma once

#include <GCrisp/Core/Core.h>
#include <GCrisp/Events/Event.h>
// #include <GCrisp/Renderer/Context.h>

namespace GCrisp {
using EventCallbackFunc = std::function<void(Event&)>;

enum class Backend { None = 0, OpenGL = 1 };

struct Version {
    Version(const uint32_t variant = 0, const uint32_t major = 1,
            const uint32_t minor = 0, const uint32_t patch = 0) {
        Variant = variant;
        Major = major;
        Minor = minor;
        Patch = patch;
    }

    std::string_view GetName() const {
        const size_t len = 256;
        char buf[len];
        snprintf(buf, len, "%d-%d.%d.%d", Variant, Major, Minor, Patch);

        return buf;
    }

    std::string_view GetNameNoVariant() {
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

struct GraphicsSpec {
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

struct WindowData {
    std::string Title = ENGINE_NAME;
    uint32_t Width = 1280, Height = 720;
    bool VSync = true;
    bool Resizable = true;

    EventCallbackFunc EventCallback = nullptr;
};

struct WindowSpecification {
    ::GCrisp::Backend Backend;
    WindowData Data = {};
};

class Window {
  public:
    Window(const WindowSpecification& spec) : m_Spec(spec) {
        s_Backend = spec.Backend;
    };
    virtual ~Window() = default;

    virtual void OnUpdate() = 0;
    virtual void TransferContext() = 0;

    // virtual void ConvertWindowCoords(glm::vec3& coords) = 0;

    inline uint32_t GetWidth() const { return m_Spec.Data.Width; }
    inline uint32_t GetHeight() const { return m_Spec.Data.Height; }
    inline GraphicsSpec GetGraphicsSpec() const { return m_GraphicsSpec; }

    virtual void SetResizable(bool enabled) = 0;
    inline bool IsResizable() const { return m_Spec.Data.Resizable; }

    inline virtual void* GetWindowPointer() = 0;
    // inline virtual Graphics::Context* GetContext() = 0;

    virtual void SetVSync(bool enabled) = 0;
    inline bool HasVSync() const { return m_Spec.Data.VSync; }

    void SetEventCallback(const EventCallbackFunc& callback) {
        m_Spec.Data.EventCallback = callback;
    };

    static Backend GetBackend() { return s_Backend; }
    static Window* Create(const WindowSpecification& spec);

  protected:
    WindowSpecification m_Spec;
    GraphicsSpec m_GraphicsSpec;

    static Backend s_Backend;

    virtual void Init() = 0;
    virtual void Shutdown() = 0;
};
} // namespace GCrisp

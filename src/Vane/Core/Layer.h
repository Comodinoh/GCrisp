#pragma once

#include <Vane/Core/Timing.h>
#include <Vane/Events/Event.h>

namespace Vane {
class Layer {
  public:
    Layer(const std::string& name = "Layer");
    virtual ~Layer();

    virtual void OnAttach() {}

    virtual void OnDetach() {}

    virtual void OnUpdate(const ProcessedTime&) {}

    virtual void OnEvent(Event&) {}

    inline const std::string& GetName() const { return m_DebugName; }

  private:
    std::string m_DebugName;
    float m_Time;
};
} // namespace Vane

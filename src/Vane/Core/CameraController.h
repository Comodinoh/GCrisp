#pragma once

#include <Vane/Core/Timing.h>
#include <Vane/Events/ApplicationEvent.h>
#include <Vane/Events/MouseEvent.h>
#include <Vane/Renderer/OrthoCamera.h>

namespace Vane {
class OrthoCameraController {
  public:
    OrthoCameraController(float aspectRatio, float moveSpeed = 1.0f,
                          bool rotation = false, float rotationSpeed = 120.0f);

    void OnUpdate(const ProcessedTime& time);
    void OnEvent(Event& e);

    inline Graphics2D::OrthoCamera& GetCamera() { return m_Camera; }

  private:
    bool OnWindowResize(WindowResizeEvent& e);
    bool OnMouseScrolled(MouseScrolledEvent& e);

  private:
    float m_MoveSpeed;
    bool m_Rotation;
    float m_RotationSpeed;
    Graphics2D::OrthoCamera m_Camera;
};
} // namespace Vane

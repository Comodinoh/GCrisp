#include "CameraController.h"

#include <Vane/Core/Input.h>
#include <Vane/Events/ApplicationEvent.h>
#include <Vane/Events/MouseEvent.h>
#include <Vane/Renderer/Camera.h>

namespace Vane {
OrthoCameraController::OrthoCameraController(float aspectRatio, float moveSpeed,
                                             bool rotation, float rotationSpeed)
    : m_MoveSpeed(moveSpeed), m_RotationSpeed(rotationSpeed),
      m_Rotation(rotation), m_Camera({0, 0, 0}, aspectRatio) {}

void OrthoCameraController::OnEvent(Event& e) {
    EventDispatcher dispatcher(e);

    dispatcher.Dispatch<WindowResizeEvent>(
        VANE_BIND_FN1(OrthoCameraController::OnWindowResize));
    dispatcher.Dispatch<MouseScrolledEvent>(
        VANE_BIND_FN1(OrthoCameraController::OnMouseScrolled));
}

void OrthoCameraController::OnUpdate(const ProcessedTime& delta) {
    /*float scale = m_Camera.GetScale();*/
    /*float mul =
     * (cos(std::chrono::steady_clock::now().time_since_epoch().count()/1000000000.0f)+1.0f)/2.0f;
     */

    /*scale *= mul*0.25f; */

    /*VANE_CORE_TRACE("{0}", scale);*/
    /*scale += 0.25f;*/

    /*m_Camera.SetScale(scale);*/
    glm::vec3 direction = glm::vec3(0);
    if (Input::IsKeyPressed(Input::W)) {
        direction.y += 1;
    }
    if (Input::IsKeyPressed(Input::S)) {
        direction.y -= 1;
    }
    if (Input::IsKeyPressed(Input::D)) {
        direction.x += 1;
    }
    if (Input::IsKeyPressed(Input::A)) {
        direction.x -= 1;
    }

    if (glm::length(direction) != 0.0f) {
        glm::vec3 velocity = glm::normalize(direction) * m_MoveSpeed;
        m_Camera.SetPosition(m_Camera.GetPosition() +
                             velocity * delta.GetSeconds());
    }

    m_Camera.Project();
}

bool OrthoCameraController::OnWindowResize(WindowResizeEvent& e) {
    m_Camera.OnResize(e.GetNewWidth(), e.GetNewHeight());
    return false;
}

bool OrthoCameraController::OnMouseScrolled(MouseScrolledEvent& e) {
    float add = e.GetYOffset() * 0.25f * m_MoveSpeed;
    float scale = m_Camera.GetScale();
    scale -= add;

    if (scale - 0.25f <= 0.0f) {
        scale -= scale - 0.25f;
    }

    m_Camera.SetScale(scale);
    return false;
}
} // namespace Vane

#include "Camera.h"

#include <GCrisp/Core/Application.h>

namespace GCrisp{

namespace Graphics{

Camera::Camera(const CameraSpec& spec) {
  m_Specification.Position = spec.Position;
  m_Specification.Rotation = spec.Rotation;
  m_Specification.View = spec.View;
  m_Specification.Projection = spec.Projection;
  m_Specification.Scale = spec.Scale;

  auto& window = Application::Get().GetWindow();
  m_Specification.AspectRatio = window.GetWidth()/window.GetHeight();
}

void Camera::Project(ProjectionCallback callback)
{
  callback(m_Specification);
}

void Camera::OnResize(int newWidth, int newHeight)
{
  m_Specification.AspectRatio = newWidth/newHeight;

  float aspectRatio = m_Specification.AspectRatio;
  float scale = m_Specification.Scale;
  m_Specification.Projection = glm::ortho(-aspectRatio*scale, aspectRatio*scale, -(1/aspectRatio)*scale, (1/aspectRatio)*scale, -1.0f, 1.0f);
}

}
}

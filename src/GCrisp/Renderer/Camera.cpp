#include "Camera.h"

#include <GCrisp/Core/Application.h>

namespace GCrisp{

namespace Graphics{

Camera::Camera(const CameraSpec& spec) : m_Specification(spec) {
  float aspectRatio = spec.AspectRatio;
  float scale = spec.Scale;
  m_Specification.Projection = glm::ortho(-aspectRatio*scale, aspectRatio*scale, -scale, scale);
}

void Camera::Project(ProjectionCallback callback)
{
  callback(m_Specification);
}

void Camera::OnResize(const int& newWidth, const int& newHeight)
{
  m_Specification.AspectRatio = (float)newWidth/(float)newHeight;

  float aspectRatio = m_Specification.AspectRatio;
  float scale = m_Specification.Scale;
  m_Specification.Projection = glm::ortho(-aspectRatio*scale, aspectRatio*scale, -scale, scale);
}

void Camera::Scale(const float& newScale)
{
  m_Specification.Scale = newScale;
  float aspectRatio = m_Specification.AspectRatio;
  m_Specification.Projection = glm::ortho(-aspectRatio*newScale, aspectRatio*newScale, -newScale, newScale);
}

void Camera::Rotate(const float& newZ)
{
  m_Specification.Rotation.z += newZ;
}

void Camera::Move(const glm::vec3& newPosition)
{
  m_Specification.Position += newPosition;
}

}
}

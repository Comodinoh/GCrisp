#pragma once

#include <GCrisp/Renderer/Camera.h>

namespace GCrisp{

namespace Graphics{

class OpenGLCamera : public Camera
{
public:
  OpenGLCamera(Camera::Type cameraType) : m_CameraType(cameraType) {}

  inline virtual Type GetType() const override {return m_CameraType;}
  inline virtual glm::mat4 GetViewProj() const override {return m_ViewProj;}
private:
  glm::mat4 m_ViewProj;
  Type m_CameraType;
};

}

}

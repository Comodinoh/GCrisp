#pragma once

#include <glm/glm.hpp>

namespace GCrisp{

namespace Graphics{

class Camera 
{
public:
  virtual ~Camera() = default;
public:
  enum class Type
  {
    None = 0, Perspective, Orthographic
  };

  inline virtual Type GetType() const = 0;
  inline virtual glm::mat4 GetViewProj() const = 0;
};

}

}

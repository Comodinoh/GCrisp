#pragma once


#include <GCrisp/Events/ApplicationEvent.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace GCrisp{

namespace Graphics{


class Camera 
{
public:
  struct CameraSpec
  {
    glm::vec3 Position;
    glm::vec3 Rotation;
    glm::mat4 View;
    glm::mat4 Projection;
    float     Scale;
    float     AspectRatio;

    CameraSpec(glm::vec3 position, glm::vec3 rotation, glm::mat4 view, glm::mat4 projection, float scale)
      : Position(position), Rotation(rotation), View(view), Projection(projection), Scale(scale) {}

    CameraSpec() : CameraSpec(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), 
                              glm::mat4(1.0f), glm::mat4(1.0f), 1.0f) {}

    glm::mat4 GetViewProj() const
    {
      return Projection*View; 
    }
  };
  using ProjectionCallback = void (*)(CameraSpec&); 
public:
  Camera(const CameraSpec& spec);
  virtual ~Camera() = default;

  void Project(ProjectionCallback callback);
  void OnResize(int newWidth, int newHeight);

  inline CameraSpec& GetSpecification() {return m_Specification;} 
public:
  static ProjectionCallback OrthographicProjection()
  {
    return [](CameraSpec& spec)
    {
      glm::vec3 pos = spec.Position;
      glm::vec3 rotation = spec.Rotation;
      glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos);
      transform *=  glm::rotate(transform, rotation.z, glm::vec3(0, 0, 1));
      spec.View = glm::inverse(transform);
    };
  }
private:
  CameraSpec m_Specification;
};

}

}

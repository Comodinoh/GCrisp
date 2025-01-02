#include "gcpch.h"
#include "CameraController.h"

#include <GCrisp/Renderer/Camera.h>
#include <GCrisp/Events/ApplicationEvent.h>
#include <GCrisp/Events/MouseEvent.h>
#include <GCrisp/Core/Input.h>

namespace GCrisp{

OrthoCameraController::OrthoCameraController(float aspectRatio, float moveSpeed, bool rotation, float rotationSpeed) : m_MoveSpeed(moveSpeed), m_RotationSpeed(rotationSpeed),  m_Rotation(rotation),
  m_Camera({{0, 0, 0}, {0, 0, 0}, aspectRatio, 1.0f}){}

void OrthoCameraController::OnEvent(Event& e)
{
  EventDispatcher dispatcher(e);

  dispatcher.Dispatch<WindowResizeEvent>(GC_BIND_FN1(OrthoCameraController::OnWindowResize));
  dispatcher.Dispatch<MouseScrolledEvent>(GC_BIND_FN1(OrthoCameraController::OnMouseScrolled));
}

void OrthoCameraController::OnUpdate(const ProcessedTime& delta)
{
  glm::vec3 direction = glm::vec3(0);
  if(Input::IsKeyPressed(Input::W))
  {
    direction.y += 1;
  }
  if(Input::IsKeyPressed(Input::S))
  {
    direction.y -= 1;
  }
  if(Input::IsKeyPressed(Input::D))
  {
    direction.x += 1;
  }
  if(Input::IsKeyPressed(Input::A))
  {
    direction.x -= 1;
  }

  glm::vec3 velocity = glm::length(direction) != 0 ? glm::normalize(direction)*m_MoveSpeed : glm::vec3(0.0f);
  m_Camera.Move(velocity*delta.GetSeconds());

  if(m_Rotation)
  {
    float rot = 0.0f;
    if(Input::IsKeyPressed(Input::Q))
    {
      rot -= 1.0f;
    } 
    if(Input::IsKeyPressed(Input::E))
    {
      rot += 1.0f;
    }
    
    m_Camera.Rotate(rot*m_RotationSpeed*delta);
  }


  /*m_Camera.Project(Graphics::Camera::OrthographicProjection());*/
}

bool OrthoCameraController::OnWindowResize(WindowResizeEvent& e)
{
  m_Camera.OnResize(e.GetNewWidth(), e.GetNewHeight());
  return false;
}

bool OrthoCameraController::OnMouseScrolled(MouseScrolledEvent& e)
{
  float scale = e.GetYOffset();
  m_Camera.Scale(m_Camera.GetSpecification().Scale+scale);
  return false;
}


}

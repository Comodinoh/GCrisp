#pragma once

#include "GCrisp/Layer.h"
namespace gcrisp{

class ImGuiLayer : public Layer
{
public:
  ImGuiLayer();
  ~ImGuiLayer();
  
  virtual void OnAttach();
  virtual void OnDetach();
  virtual void OnUpdate();
  virtual void OnEvent(Event& e);

private:

};

}

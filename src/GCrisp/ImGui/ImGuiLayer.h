#pragma once

#include "GCrisp/Layer.h"
namespace gcrisp{

class ImGuiLayer : public Layer
{
public:
  ImGuiLayer() : Layer("ImGuiLayer") {};
  virtual ~ImGuiLayer();
  
  virtual void OnAttach() override;
  virtual void OnDetach() override;
  virtual void OnUpdate() override;
  virtual void OnEvent(Event& e) override;

private:

};

}

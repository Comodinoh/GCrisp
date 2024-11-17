#include "ImGuiLayer.h"
#include "GCrisp/Application.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <imgui.h>

namespace gcrisp{

ImGuiLayer::~ImGuiLayer()
{
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}

void ImGuiLayer::OnUpdate()
{
  ImGui_ImplGlfw_NewFrame();
  ImGui_ImplOpenGL3_NewFrame();

  ImGui::NewFrame();
  ImGui::ShowDemoWindow();

  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiLayer::OnEvent(Event& e)
{
  
}

void ImGuiLayer::OnAttach()
{
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();

  ImGuiIO& io = ImGui::GetIO();
  io.ConfigFlags = ImGuiConfigFlags_NavEnableKeyboard;

  ImGui_ImplGlfw_InitForOpenGL(Application::Get().getWindow().GetWindowPointer(), true);
  ImGui_ImplOpenGL3_Init("#version 330");
}

void ImGuiLayer::OnDetach()
{
}

}

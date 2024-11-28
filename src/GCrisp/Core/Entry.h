extern GCrisp::Application* GCrisp::CreateApplication(); 

int main(int argc, char** argv)
{
  GCrisp::Log::Init();
  GCrisp::Log::GetCoreLogger()->info("Initialized Logger!");

  auto app = GCrisp::CreateApplication();
  app->Run();
  delete app;
}

extern gcrisp::Application* gcrisp::CreateApplication(); 

int main(int argc, char** argv)
{
  gcrisp::Log::Init();
  gcrisp::Log::GetCoreLogger()->warn("Initialized Logger!");
  gcrisp::Log::GetClientLogger()->info("Initialized Logger!");

  auto app = gcrisp::CreateApplication();
  app->Run();
  delete app;
}

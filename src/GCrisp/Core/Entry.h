extern gcrisp::Application* gcrisp::CreateApplication(); 

int main(int argc, char** argv)
{
  gcrisp::Log::Init();
  gcrisp::Log::GetCoreLogger()->info("Initialized Logger!");

  auto app = gcrisp::CreateApplication();
  app->Run();
  delete app;
}

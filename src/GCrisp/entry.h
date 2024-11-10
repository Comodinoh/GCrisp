extern gcrisp::Application* gcrisp::CreateApplication(); 

int main(int argc, char** argv)
{
  auto app = gcrisp::CreateApplication();
  app->Run();
  delete app;
}

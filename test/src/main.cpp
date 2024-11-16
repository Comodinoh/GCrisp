#include <GCrisp/Gcrisp.h>

class TestApplication : public gcrisp::Application
{
public:
  ~TestApplication()
  {

  }
};

gcrisp::Application* gcrisp::CreateApplication()
{
  return new TestApplication();
}


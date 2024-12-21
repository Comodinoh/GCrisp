# Introduction
Hi! 

GCrisp is a project that I've been wanting to do for ages. 
It's a game engine written in C++ to make creating multilingual Visual Novels easier
and more flexible for all types of stories and styles.

Since I'm a beginner to this kind of thing,
please bear with me if I make any mistakes along the way. I will dedicate as much time as I can
to the development of this engine, but between school and personal life, 
the progress I make will be a bit uneven. Still, I'm excited and motivated to see this through
and to work through the hardships that I might encounter along this road!

For this engine, I am planning to support multiple rendering APIs, like OpenGL, Vulkan and DirectX 
(I haven't decided which version to use yet, so feel free to send in any suggestions).
The goal is to make it compatible with Windows, Linux, Android (if I can)
and maybe IOS and/or MacOS too, if I have the time to figure out Metal as the backend rendering API.
I'll try to make the engine as easy-to-use as possible, while still focusing on efficiency and performance.
I know this will be a big challenge to tackle, but it sounds pretty fun and I'd like to try that.

The engine architecture is inspired by the Hazel game engine series made by [TheCherno](https://www.youtube.com/@TheCherno) on YouTube.
I've been learning a lot from watching him and I hope you can check it out for yourself too.

If you want to help in any way or have advice or suggestions, feel free to let me know 
and we can discuss further! Thanks for checking this out and I hope this community will be fun!

# Usage
## Linux
__Note:__ CMake >= 3.30.4 required

To use GCrisp in your project, you can import it with CMake by making a submodule:
```bash
    git submodule add https://github.com/Comodinoh/GCrisp.git lib/GCrisp
    git submodule update --init --remote --recursive lib/GCrisp
```

Then add that folder as a subdirectory in your `CMakeLists.txt` file and link the library with:
```CMake 
    add_subdirectory(lib/GCrisp)
    target_link_libraries(${PROJECT_NAME} PUBLIC gcrisp)
```
    
Now you can use the header of the library and create applications with it:

```c++
#include <GCrisp/GCrisp.h>
#include <GCrisp/Renderer/Renderer.h>
#include <GCrisp/Renderer/Shader.h>
#include <GCrisp/Renderer/Buffer.h>
#include <GCrisp/Renderer/VertexArray.h>

using namespace GCrisp;

class TestLayer : public GCrisp::Layer
{
public:
  TestLayer() : GCrisp::Layer("Test")
  {
    auto& app = Application::Get();
    m_VertexArray.reset(app.GetGraphicsCreator()->CreateVertexArray());

    float vertices[] = 
    {
     -1.0,  1.0, 0.0,   1.0, 0.0, 0.0, 1.0,
     -1.0, -1.0, 0.0,   0.0, 1.0, 0.0, 1.0,
      1.0,  1.0, 0.0,   0.0, 0.0, 1.0, 1.0,
      1.0, -1.0, 0.0,   1.0, 1.0, 1.0, 1.0
    };

    m_VertexBuffer.reset(app.GetGraphicsCreator()->CreateVertexBuffer(vertices, sizeof(vertices)));

    Graphics::BufferLayout layout = 
    {
        {"a_Position", Graphics::ShaderDataType::Float3},
        {"a_Color", Graphics::ShaderDataType::Float4}
    };

    m_VertexBuffer->SetLayout(layout);
    m_VertexArray->AddVertexBuffer(m_VertexBuffer);

    uint32_t indices[] =
    {
        0, 1, 2,
        2, 1, 3
    };
    m_IndexBuffer.reset(app.GetGraphicsCreator()->CreateIndexBuffer(indices, sizeof(indices)));
    m_VertexArray->SetIndexBuffer(m_IndexBuffer);

    std::string vertexSrc = R"(
      #version 330 core

      in vec3 a_Position;
      in vec4 a_Color;

      out vec4 color;
      out vec3 position;

      void main()
      {
        position = (a_Position+1.0)*0.5;
        color = a_Color;
        gl_Position = vec4(a_Position, 1.0);
      }
    )";
    std::string fragmentSrc = R"(
      #version 330 core

      in vec4 color;
      in vec3 position;

      out vec4 fragColor;

      void main()
      {
        fragColor = color;
      }
    )";


    m_Shader.reset(app.GetGraphicsCreator()->CreateShader(&vertexSrc, &fragmentSrc));
  }
  
  ~TestLayer()
  {

  }

  void OnUpdate() override
  { 
    Graphics::Renderer::Clear({1, 0, 0, 1});

    m_Shader->Bind();
    Graphics::Renderer::Draw(m_VertexArray);
  }

  void OnEvent(GCrisp::Event& e) override
  {
    GC_TRACE("{0}", e);
  }

private:
  std::shared_ptr<Graphics::Shader> m_Shader;
  std::shared_ptr<Graphics::VertexBuffer> m_VertexBuffer;
  std::shared_ptr<Graphics::IndexBuffer> m_IndexBuffer;
  std::shared_ptr<Graphics::VertexArray> m_VertexArray;
};

class TestApplication : public GCrisp::Application
{
public:
  TestApplication()
  {
    PushLayer(new TestLayer());
  }

  ~TestApplication()
  {
  }
};

GCrisp::Application* GCrisp::CreateApplication()
{
  return new TestApplication();
}


```

# Getting Started

I recommend checking out the [wiki](https://github.com/Comodinoh/GCrisp/wiki) to get started with GCrisp (Still work in progress!).

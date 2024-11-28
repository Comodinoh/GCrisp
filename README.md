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

class TestLayer : public GCrisp::Layer
{
public:
  TestLayer() : GCrisp::Layer("Test"){}
  ~TestLayer() {}

  void OnUpdate() override
  {
        // Loop update
  }

  void OnEvent(gcrisp::Event& e) override
  {
        // Listen for events
  }
};

class TestApplication : public GCrisp::Application
{
public:
  TestApplication()
  {
    PushLayer(new TestLayer());
  }

  ~TestApplication() {}
};

GCrisp::Application* GCrisp::CreateApplication()
{
  return new TestApplication();
}

```

# Getting Started

Feel free to check out the [wiki](https://github.com/Comodinoh/GCrisp/wiki) to get started with GCrisp.

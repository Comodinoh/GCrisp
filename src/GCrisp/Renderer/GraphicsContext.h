#pragma once

namespace gcrisp{

class GraphicsContext
{
public:
  virtual void Init() = 0;
  virtual void SwapBuffers() = 0;
};

}

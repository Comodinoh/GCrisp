#pragma once

namespace GCrisp{

namespace Graphics{

class Context
{
public:
  virtual void Init() const = 0;

  virtual void SwapBuffers() const = 0;

  virtual std::string GetRendererName() const = 0;
  virtual std::string GetVendorName() const = 0;
  virtual std::string GetVersion() const = 0;
  virtual std::string GetSLVersion() const = 0;
};

}

}

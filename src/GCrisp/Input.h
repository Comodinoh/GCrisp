#pragma once

namespace gcrisp{

class Input
{
public:
  static bool IsKeyPressed(int keycode) {return s_Instance->IsKeyPressedImpl(keycode);}
protected:
  virtual bool IsKeyPressedImpl(int keycode) = 0;
private:
  Input* s_Instance;
};

}

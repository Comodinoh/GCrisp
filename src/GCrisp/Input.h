#pragma once

namespace gcrisp{

class Input
{
public:
  static bool IsKeyPressed(const int keycode);

  static bool IsMouseButtonPressed(const int button);
  static std::pair<float, float> GetMousePosition();
};

}

module gcrisp;

import std::io;
import gcrisp::engine;


fn int main(String[] args)
{
  engine::start(1280, 720, "Hello world!");
  engine::loop();
  return 0;
}

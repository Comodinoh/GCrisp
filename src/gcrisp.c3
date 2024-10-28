module gcrisp;

import std::io;
import gcrisp::engine;


fn int main(String[] args)
{
  core::start(1280, 720, "Hello world!", 60);
  core::loop();
  return 0;
}

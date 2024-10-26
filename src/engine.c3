module gcrisp::engine;

import std::io;
import raylib5::rl;

String w_title;
int w_width;
int w_height;


fn bool start(int width, int height, String title, int target_fps)
{

  w_title = title;

  w_width = width;
  w_height = height;

  rl::initWindow(w_width, w_height, (ZString)w_title);

  resize(800, 600);

  rl::setTargetFPS(target_fps);

 return true;  
}

fn void stop()
{
  io::printfn("Called stop function: Stopping...");

  rl::closeWindow();
}

fn String get_title()
{
  return w_title; 
}

fn void set_title(String new_title)
{
  rl::setWindowTitle((ZString)new_title);
}

fn void resize(int n_width, int n_height)
{
  int w1 = w_width;
  int h1 = w_height;
  rl::setWindowSize(n_width, n_height);
  io::printfn("Resized window: from %dx%d to %dx%d", w1, h1, n_width, n_height);
}

fn int get_width()
{
  return w_width;
}

fn int get_height()
{
  return w_height;
}

fn void loop(){
  while(!rl::windowShouldClose()){
    rl::beginDrawing();
    {
      rl::clearBackground({0, 0, 0, 255});
      rl::drawFPS(10, 10);
    }
    rl::endDrawing();
  } 
}

module gcrisp::engine;

import std::io;
import raylib5::rl;


fn bool start(int width, int height, String title)
{

  rl::initWindow(width, height, title);

  rl::setTargetFPS(60);

 return true;  
}

fn void loop(){
  while(!rl::windowShouldClose()){
    rl::beginDrawing();
    {
      rl::drawText
      rl::clearBackground({0, 0, 0, 255});
      rl::drawFPS(10, 10);
    }
    rl::endDrawing();
  } 
}

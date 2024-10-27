module gcrisp::engine;

import std::io;
import raylib5::rl;

String w_title;
int w_width;
int w_height;
int ups;
DString debug_string = DString{};
const bool DEBUG = true;
Font debug_font;


fn bool start(int width, int height, String title, int target_fps)
{

  w_title = title;

  w_width = width;
  w_height = height;

  rl::initWindow(w_width, w_height, (ZString)w_title);
  rl::setWindowState(rl::FLAG_VSYNC_HINT);
  rl::setWindowState(rl::FLAG_MSAA_4X_HINT);

  debug_font = rl::loadFontEx("resources/fonts/ttf/ArnoPro-Display.ttf", 64, null, 0);
  rl::setTextureFilter(debug_font.texture, TextureFilter.BILINEAR);
  rl::genTextureMipmaps(&debug_font.texture);

 return true;  
}

fn void stop()
{
  io::printfn("Called stop function: Stopping...");

  rl::closeWindow();
}



fn void resize(int n_width, int n_height)
{
  int w1 = w_width;
  int h1 = w_height;
  rl::setWindowSize(n_width, n_height);
  io::printfn("Resized window: from %dx%d to %dx%d", w1, h1, n_width, n_height);
}



fn void update()
{
}

fn void render()
{
  rl::beginDrawing();
    {
      rl::clearBackground({0, 0, 0, 255});
      if(DEBUG)
      {
        debug_string.appendfn("FPS: %d", rl::getFPS());
        debug_string.appendfn("UPS: %d", ups);

        //String str_copy = debug_string.copy_str();

        //String[] split = str_copy.split("\n");
        //defer split;

        //int line = 0;
        //int size = 34;

        
        //io::printfn("Started %d", line);

        //foreach(info_string : split)
       // {
         // io::printfn("%d", line);
          ZString str = debug_string.zstr_view();
          int size = 32;
          int spacing = 1;
          rl::setTextLineSpacing(4+(int)rl::measureTextEx(debug_font, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*)_+{}:\"<>?|~", size, spacing).y);
          rl::drawTextEx(debug_font, str ,{10, 10}, size, 1, {255, 255, 255 ,255});
         // line++;
       // }

        //line = 0;


        //io::printfn("Finished %d", line);
        debug_string.clear();
      }
    }
  rl::endDrawing();
}

fn void loop(){
  float target_ms = 0.01666;
  float delta = 0.0;
  int updates = 0;
  double timer = rl::getTime();

  while(!rl::windowShouldClose()){
    delta += (rl::getFrameTime())/target_ms;

    while(delta >= 1.0)
    {
      updates++;
      update();
      delta -= 1.0;
    }

    render();

    if(rl::getTime()-timer >= 1)
    {
      ups = updates;
      updates = 0;
      timer += 1;
    }
 } 

  io::printfn("Game loop exited");
}

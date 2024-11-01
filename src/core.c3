module gcrisp::engine::core;

import std::io;
import raylib5::rl;
import gcrisp::engine::logger;
import gcrisp::engine::constants;
import gcrisp::engine::script;

String w_title;
int w_width;
int w_height;
int ups;
DString debug_string = DString{};
Font debug_font;
Shader font_shader;//TODO: Do something with the shader
ScriptProgram program;


fn bool start(int width, int height, String title)
{

  w_title = title;

  w_width = width;
  w_height = height;

  rl::setConfigFlags(rl::FLAG_VSYNC_HINT | rl::FLAG_MSAA_4X_HINT);
  rl::setTraceLogLevel(constants::DEBUG ? TraceLogLevel.INFO : TraceLogLevel.DEBUG);

  rl::initWindow(w_width, w_height, (ZString)w_title);

  debug_font = rl::loadFontEx("resources/fonts/ttf/font8.ttf", 64, null, 0);

  if(rl::isFontReady(debug_font))
  {
    rl::setTextureFilter(debug_font.texture, TextureFilter.BILINEAR);
   // Image tex_image = rl::loadImageFromTexture(debug_font.texture);
    //rl::imageBlurGaussian(&tex_image, 4);
    //debug_font.texture = rl::loadTextureFromImage(tex_image);
    rl::genTextureMipmaps(&debug_font.texture);
  }



  font_shader = rl::loadShader("resources/shaders/font-vert.glsl", "resources/shaders/font-frag.glsl");


  Script scr;
  scr.done = mem::malloc(bool.sizeof);
  *scr.done = false;

  Scene scene;

  ActionPair action = actions::createAction(fn(args) => logger::log("Hello! This is a script."));

  scene.register(action);
  

  scr.scenes.push(scene);

  program.scripts["main"] = scr;
  program.currentScript = "main";

  return true;
}

fn void stop()
{
  logger::log("Called stop function: Cleaning up...");

  program.dispose();

  rl::unloadFont(debug_font);
  rl::unloadShader(font_shader);

  rl::closeWindow();
}



fn void resize(int n_width, int n_height)
{
  int w1 = w_width;
  int h1 = w_height;
  rl::setWindowSize(n_width, n_height);
  logger::log("Resized window: from %dx%d to %dx%d", w1, h1, n_width, n_height);
}



fn void update()
{
  program.update();
}

fn void render()
{
 

      rl::beginDrawing();

      rl::clearBackground({0, 0, 0, 1});

      if(constants::DEBUG)
      {
        debug_string.appendfn("Fps: %d", rl::getFPS());
        debug_string.appendfn("Ups: %d", ups);

        ZString str = debug_string.zstr_view();
        int size = 64;
        int spacing = 1;
        rl::beginShaderMode(font_shader);

        rl::setTextLineSpacing(4+(int)rl::measureTextEx(debug_font, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*)_+{}:\"<>?|~", size, spacing).y);
        rl::drawTextEx(debug_font, str ,{10, 10}, size, 1, {0, 124, 255 ,255});

        rl::endShaderMode();
        debug_string.clear();
      }


      rl::endDrawing();
}

fn void loop(){

  defer {
    stop();
  }

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

  logger::log("Game loop exited");

}

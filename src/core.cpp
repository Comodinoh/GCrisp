#include <GCrisp/core.h>
#include <SDL3/SDL.h>
#include <cstdlib>
#include <sys/types.h>

namespace gcrisp{
  
  GameEngine::GameEngine(GCrispCoreInfo info)
  {
    game_info = info;
  }

  GameEngine::~GameEngine()
  {
  }
}


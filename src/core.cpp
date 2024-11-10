#include <GCrisp/core.h>
#include <SDL3/SDL.h>
#include <cstdlib>
#include <sys/types.h>
#include <glad/glad.h>
#include <glm/glm.hpp>

namespace gcrisp{
  
  GameEngine::GameEngine(GCrispCoreInfo info)
  {
    game_info = info;
  }

  GameEngine::~GameEngine()
  {
  }
}


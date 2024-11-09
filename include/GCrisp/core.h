#pragma once

#include <sys/types.h>
#include <stdlib.h>
#include <string>
#define ENGINE_NAME "GCrisp"

namespace gcrisp {
  typedef struct GCrispCoreInfo
  {
    std::string game_name;
    ushort game_version; 
  } GCrispCoreInfo;

  class GameEngine
  {
  private:
    
  public:
    GameEngine(GCrispCoreInfo info);
    ~GameEngine();

    GCrispCoreInfo game_info;
    void start();
  };
}



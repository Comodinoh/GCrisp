#pragma

#include <sys/types.h>
#include <stdlib.h>
#define ENGINE_NAME "GCrisp"

struct GCrispCoreInfo
{
  char* game_name;
  ushort game_version; 
};

struct GCrispCoreInfo* gcrisp_core_start(char* game_name, ushort game_version);


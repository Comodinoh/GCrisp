#include <GCrisp/core.h>
#include <SDL3/SDL.h>
#include <sys/types.h>

struct GCrispCoreInfo* gcrisp_core_start(char* game_name, ushort game_version)
{
  GCrispCoreInfo* core_info = (GCrispCoreInfo*) malloc(sizeof(GCrispCoreInfo));
  core_info->game_name = game_name;
  core_info->game_version = game_version;
  return core_info;
}


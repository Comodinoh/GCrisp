#pragma once

#include <sys/types.h>
#include <stdlib.h>
#define ENGINE_NAME "GCrisp"

typedef struct GCrispCoreInfo
{
  char* game_name;
  ushort game_version; 
} GCrispCoreInfo;

GCrispCoreInfo* gcrisp_core_start(char* game_name, ushort game_version);


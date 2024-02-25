#ifndef TRUCKER_GAME_GLOBALS_H
#define TRUCKER_GAME_GLOBALS_H

#include "engine/ecs/ECS.h"
#include "engine/resource/manager/ResourceManager.h"

extern ECS* ecs;
extern ResourceManager* resourceManager;

const unsigned int WINDOW_WIDTH = 1920;
const unsigned int WINDOW_HEIGHT = 1080;

const unsigned int VIEWPORT_WIDTH = 1920;
const unsigned int VIEWPORT_HEIGHT = 1080;

#endif //TRUCKER_GAME_GLOBALS_H

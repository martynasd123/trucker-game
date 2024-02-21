#ifndef TRUCKER_GAME_DEFINITIONS_H
#define TRUCKER_GAME_DEFINITIONS_H

#include <bitset>

using namespace std;

const unsigned int MAX_PASSES = 10;

using MeshId = size_t;
using LightId = size_t;
using PassId = std::bitset<MAX_PASSES>;

const size_t MAX_OBJECTS = 128;
const size_t MAX_LIGHTS = 20;

const PassId SHADOW_PASS = 1;
const PassId GEOMETRY_PASS = 1 << 1;
const PassId LIGHTING_PASS = 1 << 2;
const PassId POST_PROCESS_PASS = 1 << 3;

const unsigned int MATERIAL_DATA_BINDING_POINT = 0;
const unsigned int POINT_LIGHT_DATA_BINDING_POINT = 1;

#endif //TRUCKER_GAME_DEFINITIONS_H

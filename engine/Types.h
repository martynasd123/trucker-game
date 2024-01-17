//
// Created by Martynas Dargis on 17.01.24.
//

#ifndef TRUCKER_GAME_TYPES_H
#define TRUCKER_GAME_TYPES_H

#include <bitset>

const int MAX_ENTITIES = 64;
const int MAX_COMPONENTS = 16;

using Entity = int;
using ComponentType = int;
using Signature = std::bitset<MAX_ENTITIES>;

#endif //TRUCKER_GAME_TYPES_H

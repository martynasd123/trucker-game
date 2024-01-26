#ifndef TRUCKER_GAME_TYPES_H
#define TRUCKER_GAME_TYPES_H

#include <bitset>

const int MAX_COMPONENTS = 64;
const int MAX_SYSTEMS = 32;

using Entity = int;
using ComponentSignature = std::bitset<MAX_COMPONENTS>;
using ArchetypeSignature = std::bitset<MAX_COMPONENTS>;
using SystemSignature = std::bitset<MAX_COMPONENTS>;

using SystemLayer = std::bitset<MAX_SYSTEMS>;

const SystemLayer GAME_LOGIC_LAYER = SystemLayer(1);
const SystemLayer PHYSICS_LAYER = SystemLayer(1) << 1;
const SystemLayer COSMETIC_LAYER = SystemLayer(1) << 2;

#endif //TRUCKER_GAME_TYPES_H

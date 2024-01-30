#ifndef TRUCKER_GAME_RESOURCE_TYPES_H
#define TRUCKER_GAME_RESOURCE_TYPES_H

#include <utility>
#include <string>

using ResourceHandle = unsigned int;
using ResourceResolverId = unsigned int;
using ResourcePath = std::string;

const unsigned int MAX_RESOURCE_RESOLVERS = 32;
const unsigned int MAX_RESOURCES = 64;

#endif //TRUCKER_GAME_RESOURCE_TYPES_H

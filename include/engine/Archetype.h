#ifndef TRUCKER_GAME_ARCHETYPE_H
#define TRUCKER_GAME_ARCHETYPE_H

#include <engine/Types.h>

class Archetype {
public:
    ArchetypeSignature mSignature;
    // Holds components in contiguous arrays for each component type
    std::unordered_map<ComponentSignature, char*> mComponentData;
    std::vector<Entity> mEntities;
    // Number of entities that can be fit into currently allocated memory
    std::size_t mCapacity;
};


#endif //TRUCKER_GAME_ARCHETYPE_H

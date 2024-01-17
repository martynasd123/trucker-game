//
// Created by Martynas Dargis on 17.01.24.
//

#ifndef TRUCKER_GAME_ENTITYMANAGER_H
#define TRUCKER_GAME_ENTITYMANAGER_H


#include <queue>
#include "Types.h"

class EntityManager {
private:
    // A queue of all available IDs
    std::queue<Entity> m_available_ids;
    // Stores component signature of each entity
    std::array<Signature, MAX_ENTITIES> m_signatures;
public:
    EntityManager();
    Entity createEntity();
    void removeEntity(Entity entity);
    Signature getSignature(Entity entity);
    void setSignature(Entity entity, Signature signature);
};


#endif //TRUCKER_GAME_ENTITYMANAGER_H

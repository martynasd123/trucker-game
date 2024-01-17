//
// Created by Martynas Dargis on 17.01.24.
//

#include <cassert>
#include "EntityManager.h"

Entity EntityManager::createEntity() {
    Entity entity = m_available_ids.front();
    m_available_ids.pop();
    return entity;
}

void EntityManager::removeEntity(Entity entity) {
    m_signatures[entity] = 0x00;
    m_available_ids.push(entity);
}

Signature EntityManager::getSignature(Entity entity) {
    auto signature = m_signatures[entity];
    assert(signature != NULL && "No signature set for entity");
    return m_signatures[entity];
}

void EntityManager::setSignature(Entity entity, Signature signature) {
    m_signatures[entity] = signature;
}

EntityManager::EntityManager() {
    for (int i = 0; i < MAX_ENTITIES; ++i) {
        m_available_ids.push(i);
    }
}

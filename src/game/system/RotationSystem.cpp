#include "game/system/RotationSystem.h"
#include "engine/Globals.h"

void RotationSystem::update(long dt, std::vector<Entity> entities) {
    for (Entity& entity: entities) {
        auto transformComponent = ecs->getComponent<TransformComponent>(entity);
        auto currentOrientation = transformComponent->orientation;
        transformComponent->orientation = make_shared<Quaternion>(currentOrientation->rotateX(0.01f));
        transformComponent->is_dirty = true;
    }
}

void RotationSystem::entityRemoved(Entity entity)
{
}

void RotationSystem::entityAdded(Entity entity)
{
}

void RotationSystem::init()
{
}

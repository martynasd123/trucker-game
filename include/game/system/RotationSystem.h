#ifndef TRUCKER_GAME_ROTATIONSYSTEM_H
#define TRUCKER_GAME_ROTATIONSYSTEM_H

#include "engine/ecs/System.h"
#include "game/component/TransformComponent.h"

class RotationSystem : public System<TransformComponent>
{
public:
    void update(long dt, std::vector<Entity> entities) override;
    void entityRemoved(Entity entity) override;
    void entityAdded(Entity entity) override;
    void init() override;
};

#endif // TRUCKER_GAME_ROTATIONSYSTEM_H
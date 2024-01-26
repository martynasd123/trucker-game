#include "engine/ECS.h"
#include "game/component/PositionComponent.h"
#include "game/component/RenderComponent.h"
#include "game/system/OpenGLRenderingSystem.h"

ECS* ecs = new ECS;

int main() {
    ecs->registerComponent<PositionComponent>();
    ecs->registerComponent<RenderComponent>();

    auto openGLSystem = new OpenGLRenderingSystem;
    ecs->registerSystem(COSMETIC_LAYER, openGLSystem);

    Entity e1 = ecs->createEntity();
    ecs->addComponent<PositionComponent>(e1, Vector3f{0.0f, 10.0f});
    ecs->addComponent<RenderComponent>(e1);


    ecs->runSystems(COSMETIC_LAYER | PHYSICS_LAYER | GAME_LOGIC_LAYER, 0.0f);

    delete ecs;

    return 0;
}

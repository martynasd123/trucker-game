#include "engine/ecs/ECS.h"
#include "game/component/PositionComponent.h"
#include "game/component/RenderComponent.h"
#include "game/system/OpenGLRenderingSystem.h"
#include "common/math/Vector3f.h"
#include "engine/resource/manager/ResourceManager.h"
#include "engine/resource/TextResource.h"
#include "engine/resource/resolver/TextResourceResolver.h"
#include "engine/resource/resolver/MeshResourceResolver.h"

#include <thread>

ECS* ecs = new ECS;

void loop() {
    using namespace std::chrono;

    const static auto TIME_PER_STEP = milliseconds(1000L / 60L);
    const static auto TARGET_RENDER_PERIOD = milliseconds(1000L / 120L);

    auto gameTime = high_resolution_clock::now();
    auto renderTime = high_resolution_clock::now();
    while (true) {
        auto currentTime = high_resolution_clock::now();
        while (currentTime <= gameTime) {
            gameTime += TIME_PER_STEP;
            ecs->runSystems(PHYSICS_LAYER | GAME_LOGIC_LAYER,
                            duration_cast<duration<float>>(TIME_PER_STEP).count());
        }
        currentTime = high_resolution_clock::now();
        if (currentTime - renderTime < TARGET_RENDER_PERIOD) {
            std::this_thread::sleep_for((renderTime + TARGET_RENDER_PERIOD) - currentTime);
            currentTime = high_resolution_clock::now();
        }
        ecs->runSystems(COSMETIC_LAYER, duration_cast<duration<float>>(currentTime - renderTime).count());
        renderTime = currentTime;
    }
}

int main() {
    auto resManager = ResourceManager();

    resManager.registerResourceResolver<TextResourceResolver>();
    resManager.registerResourceResolver<MeshResourceResolver>();

    auto handle = resManager.acquireHandle<MeshResource>("assets/meshes/cube.mesh");
    auto mesh = resManager.getResource<MeshResource>(handle);

    resManager.releaseResource(handle);

    ecs->registerComponent<PositionComponent>();
    ecs->registerComponent<RenderComponent>();

    auto openGLSystem = new OpenGLRenderingSystem;
    ecs->registerSystem(COSMETIC_LAYER, openGLSystem);
    openGLSystem->init();

    Entity e1 = ecs->createEntity();
    ecs->addComponent<PositionComponent>(e1, Vector3f{0.0f, 10.0f, 0.0f});
    ecs->addComponent<RenderComponent>(e1);

    loop();

    delete ecs;
    return 0;
}

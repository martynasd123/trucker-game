#include "engine/ecs/ECS.h"
#include "game/component/RenderComponent.h"
#include "game/system/OpenGLRenderingSystem.h"
#include "game/system/RotationSystem.h"
#include "common/math/Vector3f.h"
#include "common/math/Quaternion.h"
#include "engine/resource/manager/ResourceManager.h"
#include "engine/resource/TextResource.h"
#include "engine/resource/resolver/TextResourceResolver.h"
#include "engine/resource/resolver/MeshResourceResolver.h"

#include <thread>
#include <iostream>

ECS* ecs = new ECS;
ResourceManager* resourceManager = new ResourceManager;

void loop() {
    using namespace std::chrono;

    const static auto TIME_PER_STEP = milliseconds(1000L / 60L);
    const static auto TARGET_RENDER_PERIOD = milliseconds(1000L / 120L);

    auto gameTime = high_resolution_clock::now();
    auto renderTime = high_resolution_clock::now();
    while (true) {
        auto currentTime = high_resolution_clock::now();
        while (currentTime >= gameTime) {
            gameTime += TIME_PER_STEP;
            ecs->runSystems(PHYSICS_LAYER | GAME_LOGIC_LAYER,
                            duration_cast<duration<float>>(TIME_PER_STEP).count());
        }
        currentTime = high_resolution_clock::now();
        if (currentTime - renderTime < TARGET_RENDER_PERIOD) {
            cout << "Sleeping for " << duration_cast<duration<float>>((renderTime + TARGET_RENDER_PERIOD) - currentTime).count() << "ms" << endl;
            std::this_thread::sleep_for((renderTime + TARGET_RENDER_PERIOD) - currentTime);
            currentTime = high_resolution_clock::now();
        }
        cout << "FPS: " << 1.0f / duration_cast<duration<float>>(currentTime - renderTime).count() << endl;
        ecs->runSystems(COSMETIC_LAYER, duration_cast<duration<float>>(currentTime - renderTime).count());
        renderTime = currentTime;
    }
}

int main() {
    resourceManager->registerResourceResolver<TextResourceResolver, TextResource>();
    resourceManager->registerResourceResolver<MeshResourceResolver, MeshResource>();

    ecs->registerComponent<TransformComponent>();
    ecs->registerComponent<RenderComponent>();

    auto openGLSystem = new OpenGLRenderingSystem;
    ecs->registerSystem(COSMETIC_LAYER, openGLSystem);
    auto rotationSystem = new RotationSystem;
    ecs->registerSystem(GAME_LOGIC_LAYER, rotationSystem);
    openGLSystem->init();

    Vector3f pos = {0.0f, 0.0f, 0.0f};
    Vector3f scale = {1.0f, 1.0f, 1.0f};

    Entity e1 = ecs->createEntity();
    ecs->addComponent<TransformComponent>(e1, pos, Quaternion::IDENTITY, scale);

    auto handle = resourceManager->acquireHandle<MeshResource>("assets/meshes/pedestal.mesh");
    auto mesh = resourceManager->getResource<MeshResource>(handle);
    ecs->addComponent<RenderComponent>(e1, mesh);

    resourceManager->releaseResource(handle);

    loop();

    delete ecs;
    delete rotationSystem;
    return 0;

}

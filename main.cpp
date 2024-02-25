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

float ttoRadians(float deg) {
    return deg * (((float)M_PI) / 180.0f);
}

int main() {
    resourceManager->registerResourceResolver<TextResourceResolver, TextResource>();
    resourceManager->registerResourceResolver<MeshResourceResolver, MeshResource>();

    ecs->registerComponent<PositionComponent>();
    ecs->registerComponent<RenderComponent>();

    auto openGLSystem = new OpenGLRenderingSystem;
    ecs->registerSystem(COSMETIC_LAYER, openGLSystem);
    openGLSystem->init();

    Entity e1 = ecs->createEntity();
    ecs->addComponent<PositionComponent>(e1, Vector3f{0.0f, 0.0f, 0.0f});

    auto handle = resourceManager->acquireHandle<MeshResource>("assets/meshes/pedestal.mesh");
    auto mesh = resourceManager->getResource<MeshResource>(handle);
    ecs->addComponent<RenderComponent>(e1, mesh);

    resourceManager->releaseResource(handle);

    loop();

    delete ecs;
    return 0;

//    Vector4f vec = Vector4f(0.0f, 0.0f, 15.0f, 1.0f) * Matrix4f::perspective(ttoRadians(60.0f), ((float)WINDOW_WIDTH) / ((float)WINDOW_HEIGHT), 100.0f, 0.1f);
//    Vector3f normalized = Vector3f(vec.getX() / vec.getW(), vec.getY() / vec.getW(), vec.getZ() / vec.getW());
//    cout << vec.getX() << " " << vec.getY() << " " << vec.getZ() << " " << vec.getW() << endl;
//    cout << normalized.getX() << " " << normalized.getY() << " " << normalized.getZ() << endl;
}

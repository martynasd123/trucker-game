#ifndef TRUCKER_GAME_OPENGLRENDERINGSYSTEM_H
#define TRUCKER_GAME_OPENGLRENDERINGSYSTEM_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "engine/Globals.h"
#include "engine/ecs/System.h"
#include "game/component/PositionComponent.h"
#include "game/component/RenderComponent.h"
#include "engine/graphics/opengl/Renderer.h"

class OpenGLRenderingSystem: public System<PositionComponent, RenderComponent> {
private:
    GLFWwindow* mWindow {};
    Renderer* mRenderer{};
public:
    void init() override;
    void update(long dt, std::vector<Entity> entities) override;
    void entityRemoved(Entity entity) override;
    void entityAdded(Entity entity) override;
};


#endif //TRUCKER_GAME_OPENGLRENDERINGSYSTEM_H

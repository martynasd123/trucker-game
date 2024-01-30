#ifndef TRUCKER_GAME_OPENGLRENDERINGSYSTEM_H
#define TRUCKER_GAME_OPENGLRENDERINGSYSTEM_H

#include "engine/ecs/System.h"
#include "game/component/PositionComponent.h"
#include "game/component/RenderComponent.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class OpenGLRenderingSystem: public System<PositionComponent, RenderComponent> {
private:
    GLFWwindow* window {};
public:
    void init() override;
    void update(long dt, std::vector<Entity> entities) override;
};


#endif //TRUCKER_GAME_OPENGLRENDERINGSYSTEM_H

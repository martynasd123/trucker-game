#ifndef TRUCKER_GAME_OPENGLRENDERINGSYSTEM_H
#define TRUCKER_GAME_OPENGLRENDERINGSYSTEM_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>

#include "engine/Globals.h"
#include "engine/ecs/System.h"
#include "game/component/RenderComponent.h"
#include "engine/graphics/opengl/Renderer.h"
#include <game/component/TransformComponent.h>

class OpenGLRenderingSystem: public System<TransformComponent, RenderComponent> {
private:
    GLFWwindow* mWindow;
    unique_ptr<Renderer> mRenderer;

    /**
     * Entity to mesh handle map. This is where we keep handles returned by the renderer that
     * correspond to the engine entities.
     */
    unordered_map<Entity, MeshId> mEntityMeshIds;

    static void frameBufferSizeCallback(GLFWwindow* window, int width, int height);
    void frameBufferSizeUpdated(int width, int height);
public:
    void init() override;
    void update(long dt, std::vector<Entity> entities) override;
    void entityRemoved(Entity entity) override;
    void entityAdded(Entity entity) override;
    ~OpenGLRenderingSystem();
};


#endif //TRUCKER_GAME_OPENGLRENDERINGSYSTEM_H

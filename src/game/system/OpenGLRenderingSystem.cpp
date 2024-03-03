#include "game/system/OpenGLRenderingSystem.h"
#include <iostream>

void OpenGLRenderingSystem::init() {
    if (!glfwInit()) {
        throw runtime_error("Failed to initialize glfw");
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    mWindow = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "This is definitely a window", nullptr, nullptr);
    if (mWindow == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(1);
    }

    int width, height;
    glfwGetFramebufferSize(mWindow, &width, &height);

    glfwSetWindowUserPointer(mWindow, this);
    glfwSetFramebufferSizeCallback(mWindow, frameBufferSizeCallback);

    glfwMakeContextCurrent(mWindow);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(1);
    }

    glEnable(GL_DEPTH_TEST);

    mRenderer = make_unique<Renderer>(width, height);
    LightId l1 = mRenderer->addLight(PointLight(Vector3f(0.05f, 0.05f, 0.05f),
                                   Vector3f(1.0f, 1.0f, 1.0f),
                                   Vector3f(1.0f, 1.0f, 1.0f),
                                   Vector3f(0.0f, 0.0f, 0.0f),
                                   1.0f,
                                   0.09f,
                                   0.032f));

}

void OpenGLRenderingSystem::frameBufferSizeCallback(GLFWwindow* window, int width, int height) {
    OpenGLRenderingSystem& system = *static_cast<OpenGLRenderingSystem*>(glfwGetWindowUserPointer(window));
    system.frameBufferSizeUpdated(width, height);
}


void OpenGLRenderingSystem::update(long dt, const std::vector<Entity> entities) {
    if (glfwWindowShouldClose(mWindow)) {
        exit(0);
    }
    mRenderer->draw();
    glfwSwapBuffers(mWindow);
    glfwPollEvents();
}

void OpenGLRenderingSystem::entityRemoved(Entity entity) {
    std::cout << "Entity removed" << std::endl;
}

void OpenGLRenderingSystem::entityAdded(Entity entity) {
    std::cout << "Entity added" << std::endl;
    auto renderComponent = ecs->getComponent<RenderComponent>(entity);
    auto positionComponent = ecs->getComponent<PositionComponent>(entity);
    if (!positionComponent || !renderComponent || !renderComponent->mesh) {
        return;
    }

    auto transform = Transform(Quaternion::IDENTITY, positionComponent->pos, Vector3f(1.0f, 1.0f, 1.0f));
    mRenderer->addMesh(*renderComponent->mesh, transform);
}

OpenGLRenderingSystem::~OpenGLRenderingSystem() {
    glfwDestroyWindow(mWindow);
    glfwTerminate();
}

void OpenGLRenderingSystem::frameBufferSizeUpdated(int width, int height) {
    mRenderer->frameBufferSizeUpdated(width, height);
}

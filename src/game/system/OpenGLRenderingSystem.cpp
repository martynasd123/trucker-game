#include "game/system/OpenGLRenderingSystem.h"
#include <iostream>
#include "game/Globals.h"

void OpenGLRenderingSystem::init() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(800, 600, "This is definitely a window", NULL, NULL);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(1);
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(1);
    }

    glViewport(0, 0, 800, 600);
}

void OpenGLRenderingSystem::update(long dt, const std::vector<Entity> entities) {
    if (glfwWindowShouldClose(window)) {
        exit(0);
    }
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void OpenGLRenderingSystem::entityRemoved(Entity entity) {
    std::cout << "Entity removed" << std::endl;
}

void OpenGLRenderingSystem::entityAdded(Entity entity) {
    std::cout << "Entity added" << std::endl;
}

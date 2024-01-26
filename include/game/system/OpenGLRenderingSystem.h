#ifndef TRUCKER_GAME_OPENGLRENDERINGSYSTEM_H
#define TRUCKER_GAME_OPENGLRENDERINGSYSTEM_H

#include "engine/System.h"
#include "game/component/PositionComponent.h"
#include "game/component/RenderComponent.h"

class OpenGLRenderingSystem: public System<PositionComponent, RenderComponent> {
public:
    void update(long dt, std::vector<Entity> entities) override;
};


#endif //TRUCKER_GAME_OPENGLRENDERINGSYSTEM_H

#ifndef TRUCKER_GAME_RENDERCOMPONENT_H
#define TRUCKER_GAME_RENDERCOMPONENT_H

#include "common/render/Mesh.h"
#include "engine/resource/MeshResource.h"

struct RenderComponent {
    Mesh* mesh{};
    RenderComponent() = default;

    explicit RenderComponent(MeshResource* meshResource) : mesh(new Mesh(*meshResource->mesh)) { }

    virtual ~RenderComponent() {
        delete mesh;
        mesh = nullptr;
    }
};


#endif //TRUCKER_GAME_RENDERCOMPONENT_H

#ifndef TRUCKER_GAME_RENDERCOMPONENT_H
#define TRUCKER_GAME_RENDERCOMPONENT_H

#include "common/render/Mesh.h"
#include "engine/resource/MeshResource.h"

struct RenderComponent {
    shared_ptr<Mesh> mesh;
    RenderComponent() = default;

    explicit RenderComponent(MeshResource* meshResource) : mesh(meshResource->mesh) { }
};


#endif //TRUCKER_GAME_RENDERCOMPONENT_H

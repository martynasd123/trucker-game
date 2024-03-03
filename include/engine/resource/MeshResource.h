#ifndef TRUCKER_GAME_MESHRESOURCE_H
#define TRUCKER_GAME_MESHRESOURCE_H

#include "Resource.h"
#include "common/render/Mesh.h"

class MeshResource: public Resource {
public:
    std::shared_ptr<Mesh> mesh;
    explicit MeshResource(std::shared_ptr<Mesh> mesh) : mesh(std::move(mesh)) {}
};

#endif //TRUCKER_GAME_MESHRESOURCE_H

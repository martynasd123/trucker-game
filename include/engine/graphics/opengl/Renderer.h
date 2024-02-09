#ifndef TRUCKER_GAME_RENDERER_H
#define TRUCKER_GAME_RENDERER_H

#include "common/render/Mesh.h"
#include "common/math/Transform.h"

using MeshId = unsigned int;

class Renderer {
public:
    MeshId addMesh(Mesh* mesh, Transform transform);
    void removeMesh(MeshId id);
    void updateTransform(MeshId id, Transform transform);
};


#endif //TRUCKER_GAME_RENDERER_H

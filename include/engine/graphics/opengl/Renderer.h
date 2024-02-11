#ifndef TRUCKER_GAME_RENDERER_H
#define TRUCKER_GAME_RENDERER_H

#include "common/render/Mesh.h"
#include "common/math/Transform.h"
#include "engine/graphics/opengl/ObjectBasedBatch.h"
#include "engine/graphics/opengl/pass/GeometryPass.h"
#include <queue>

using namespace std;

using MeshId = size_t;
const size_t MAX_OBJECTS = 128;

class Renderer {
private:
    ObjectBasedBatch* mBatches[MAX_OBJECTS]{};
    queue<MeshId> mAvailableIds;

    GeometryPass* mGeometryPass;
public:
    explicit Renderer();
    MeshId addMesh(Mesh* mesh, Transform transform);
    void removeMesh(MeshId id);
    void updateTransform(MeshId id, Transform transform);
    void draw();
};


#endif //TRUCKER_GAME_RENDERER_H

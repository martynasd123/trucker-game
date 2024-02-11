#include "engine/graphics/opengl/Renderer.h"

MeshId Renderer::addMesh(Mesh *mesh, Transform transform) {
    auto batch = new ObjectBasedBatch(mesh, transform);
    MeshId id = mAvailableIds.front();
    mAvailableIds.pop();
    mBatches[id] = batch;
    return id;
}

void Renderer::removeMesh(MeshId id) {
    delete mBatches[id];
    mBatches[id] = nullptr;
}

void Renderer::updateTransform(MeshId id, Transform transform) {
    mBatches[id]->setTransform(transform);
}

Renderer::Renderer() {
    for (int i = 0; i < MAX_OBJECTS; ++i) {
        mAvailableIds.push(i);
    }
    mGeometryPass = new GeometryPass;
}

void Renderer::draw() {
    mGeometryPass->draw(mBatches[0]);
}
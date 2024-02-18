#include "engine/graphics/opengl/Renderer.h"
#include "engine/graphics/opengl/material/BPMonochromaticMaterialHandler.h"

MeshId Renderer::addMesh(Mesh *mesh, Transform transform) {
    auto batch = new ObjectBasedBatch(mesh, transform, mHandlerRegistry);
    MeshId id = mAvailableMeshIds.front();
    mAvailableMeshIds.pop();
    mBatches[id] = batch;
    return id;
}

void Renderer::removeMesh(MeshId id) {
    delete mBatches[id];
    mBatches[id] = nullptr;
    mAvailableMeshIds.push(id);
}

void Renderer::updateTransform(MeshId id, Transform transform) {
    mBatches[id]->setTransform(transform);
}

Renderer::Renderer() : mHandlerRegistry(*new MaterialHandlerRegistry), mLightsUbo(500),
                       mAlbedoTexture(Texture2D(0, GL_RGB16F, WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGBA, GL_FLOAT)),
                       mNormalTexture(Texture2D(0, GL_RGB16F, WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGBA, GL_FLOAT)),
                       mPositionTexture(Texture2D(0, GL_RGB16F, WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGBA, GL_FLOAT)),
                       mGeometryPass(GeometryPass(mAlbedoTexture, mNormalTexture, mPositionTexture)),
                       mLightingPass(LightingPass(mLightsUbo, mPositionTexture, mNormalTexture, mAlbedoTexture, mHandlerRegistry, mTextureManager)),
                       mTextureManager(TextureManager()){

    GL_UTIL::checkError();
    for (int i = 0; i < MAX_OBJECTS; ++i) {
        mAvailableMeshIds.push(i);
    }
    for (int i = 0; i < MAX_LIGHTS; ++i) {
        mAvailableLightIds.push(i);
    }
    mHandlerRegistry.registerHandler<BPMonochromaticMaterialHandler>(*resourceManager);
}

void Renderer::draw() {
    mGeometryPass.draw(mBatches[0]);
    mLightingPass.draw();
}
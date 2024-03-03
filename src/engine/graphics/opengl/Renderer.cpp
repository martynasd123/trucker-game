#include "engine/graphics/opengl/Renderer.h"
#include "engine/graphics/opengl/material/BPMonochromaticMaterialHandler.h"

MeshId Renderer::addMesh(const Mesh &mesh, Transform transform) {
    auto batch = make_shared<ObjectBasedBatch>(mesh, transform, mHandlerRegistry);
    return mBatches.emplace_back(std::move(batch));
}

void Renderer::removeMesh(MeshId id) {
    mBatches.eraseById(id);
}

void Renderer::updateTransform(MeshId id, Transform transform) {
    mBatches[id]->setTransform(transform);
}

float toRadians(float deg) {
    return deg * (((float) M_PI) / 180.0f);
}

Renderer::Renderer(int width, int height) :
        mHandlerRegistry(),
        mPointLightsUbo(UNIFORM_BUFFER, 20, DYNAMIC_DRAW),
        mDeferredShadingTextureRegistry(width, height),
        mGeometryPass(mDeferredShadingTextureRegistry, mCam, width, height),
        mLightingPass(mPointLightsUbo, mDeferredShadingTextureRegistry, mHandlerRegistry, mTextureManager, width, height),
        mTextureManager(),
        mCam() {
    mCam.setProjection(
            Matrix4f::perspective(toRadians(60.0f), ((float) WINDOW_WIDTH) / ((float) WINDOW_HEIGHT), 100.0f, 0.1f));
    mCam.setView(Matrix4f::translation(0.0f, 0.0f, 5.0f));

    mHandlerRegistry.registerHandler<BPMonochromaticMaterialHandler>(*resourceManager);
}

void Renderer::draw() {
    mGeometryPass.draw(*mBatches[0]);
    mLightingPass.draw();
}

template<>
LightId Renderer::addLight(PointLight light) {
    auto lightCopy = make_shared<PointLight>(light);

    Vector4f vec = Vector4f(lightCopy->position, 1.0f) * mCam.getView() * mCam.getProjection();
    lightCopy->position = vec.xyz() / vec.getW();

    LightId id = mLights.emplace_back(std::move(lightCopy));
    mPointLightsUbo.addElement(light);
    return id;
}


LightId Renderer::removeLight(LightId id) {
    mPointLightsUbo.removeElement(mLights.getIndex(id));
    mLights.eraseById(id);
    return id;
}

void Renderer::frameBufferSizeUpdated(int width, int height) {
    mTextureManager.forgetTexture(mDeferredShadingTextureRegistry.getMaterialDataTexture());
    mTextureManager.forgetTexture(mDeferredShadingTextureRegistry.getAlbedoTexture());
    mTextureManager.forgetTexture(mDeferredShadingTextureRegistry.getPositionTexture());
    mTextureManager.forgetTexture(mDeferredShadingTextureRegistry.getNormalTexture());
    mDeferredShadingTextureRegistry.updateDimensions(width, height);
    mGeometryPass.updateDimensions(width, height);
    mLightingPass.updateDimensions(width, height);
}
#include "engine/graphics/opengl/Renderer.h"
#include "engine/graphics/opengl/material/BPMonochromaticMaterialHandler.h"
#include <math.h>

MeshId Renderer::addMesh(Mesh *mesh, Transform transform) {
    auto* batch = new ObjectBasedBatch(mesh, transform, mHandlerRegistry);
    MeshId id = mAvailableMeshIds.front();
    mAvailableMeshIds.pop();
    return mBatches.push_back(id, batch);
}

void Renderer::removeMesh(MeshId id) {
    mBatches.eraseById(id);
}

void Renderer::updateTransform(MeshId id, Transform transform) {
    mBatches[id]->setTransform(transform);
}

float toRadians(float deg) {
    return deg * (((float)M_PI) / 180.0f);
}

Renderer::Renderer() : mHandlerRegistry(*new MaterialHandlerRegistry), mPointLightsUbo(LightsUniformBufferObject<PointLight>(20)),
                       mAlbedoTexture(Texture2D(0, GL_RGB16F, VIEWPORT_WIDTH, VIEWPORT_HEIGHT, GL_RGBA, GL_FLOAT)),
                       mNormalTexture(Texture2D(0, GL_RGB16F, VIEWPORT_WIDTH, VIEWPORT_HEIGHT, GL_RGBA, GL_FLOAT)),
                       mPositionTexture(Texture2D(0, GL_RGB16F, VIEWPORT_WIDTH, VIEWPORT_HEIGHT, GL_RGBA, GL_FLOAT)),
                       mMaterialDataTexture(Texture2D(0, GL_RGB16F, VIEWPORT_WIDTH, VIEWPORT_HEIGHT, GL_RGBA, GL_FLOAT)),
                       mGeometryPass(GeometryPass(mAlbedoTexture, mNormalTexture, mPositionTexture, mMaterialDataTexture, mCam)),
                       mLightingPass(LightingPass(mPointLightsUbo, mPositionTexture, mNormalTexture, mAlbedoTexture, mMaterialDataTexture, mHandlerRegistry, mTextureManager)),
                       mTextureManager(TextureManager()),
                       mCam(){
    mCam.setProjection(Matrix4f::perspective(toRadians(60.0f), ((float)WINDOW_WIDTH) / ((float)WINDOW_HEIGHT), 100.0f, 0.1f));
    mCam.setView(Matrix4f::translation(0.0f,0.0f, 5.0f));

    for (int i = 0; i < MAX_OBJECTS; ++i) {
        mAvailableMeshIds.push(i);
    }
    for (int i = 0; i < MAX_LIGHTS; ++i) {
        mAvailableLightIds.push(i);
    }
    mHandlerRegistry.registerHandler<BPMonochromaticMaterialHandler>(*resourceManager);
}

void Renderer::draw() {

    mGeometryPass.draw(*mBatches[0]);
    mLightingPass.draw();
}

template<>
LightId Renderer::addLight(PointLight light) {
    auto *lightCopy = new PointLight(light);
    auto &pointLight = dynamic_cast<PointLight &>(*lightCopy);

    Vector4f vec = Vector4f(pointLight.position, 1.0f) * mCam.getView() * mCam.getProjection();
    pointLight.position = vec.xyz() / vec.getW();

    LightId id = mLights.push_back(lightCopy);
    mPointLightsUbo.addLight(id, light);
    return id;
}


LightId Renderer::removeLight(LightId id) {
    mLights.eraseById(id);
    mPointLightsUbo.removeLight(id);
    return id;
}
#include "engine/graphics/opengl/texture/DeferredShadingTextureRegistry.h"

Texture2D DeferredShadingTextureRegistry::initAlbedoTexture() const {
    Texture2D tex = Texture2D(0, GL_RGB16F, width, height, GL_RGBA, GL_FLOAT);
    tex.setParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    tex.setParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    tex.setParameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
    tex.setParameter(GL_TEXTURE_WRAP_T, GL_REPEAT);
    return tex;
}

Texture2D DeferredShadingTextureRegistry::initPositionTexture() const {
    Texture2D tex = Texture2D(0, GL_RGB16F, width, height, GL_RGBA, GL_FLOAT);
    tex.setParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    tex.setParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    tex.setParameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
    tex.setParameter(GL_TEXTURE_WRAP_T, GL_REPEAT);
    return tex;
}

Texture2D DeferredShadingTextureRegistry::initNormalTexture() const {
    Texture2D tex = Texture2D(0, GL_RGB16F, width, height, GL_RGBA, GL_FLOAT);
    tex.setParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    tex.setParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    tex.setParameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
    tex.setParameter(GL_TEXTURE_WRAP_T, GL_REPEAT);
    return tex;}

Texture2D DeferredShadingTextureRegistry::initMaterialDataTexture() const {
    Texture2D tex = Texture2D(0, GL_RGB16F, width, height, GL_RGBA, GL_FLOAT);
    tex.setParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    tex.setParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    tex.setParameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
    tex.setParameter(GL_TEXTURE_WRAP_T, GL_REPEAT);
    return tex;
}

DeferredShadingTextureRegistry::DeferredShadingTextureRegistry(GLsizei width, GLsizei height)
        : width(width), height(height),
          mAlbedoTexture(initAlbedoTexture()),
          mPositionTexture(initPositionTexture()),
          mNormalTexture(initNormalTexture()),
          mMaterialDataTexture(initMaterialDataTexture()) {}

void DeferredShadingTextureRegistry::updateDimensions(const GLsizei& pWidth, const GLsizei& pHeight) {
    this->width = pWidth;
    this->height = pHeight;

    mAlbedoTexture = initAlbedoTexture();
    mPositionTexture = initPositionTexture();
    mNormalTexture = initNormalTexture();
    mMaterialDataTexture = initMaterialDataTexture();
}

const Texture2D &DeferredShadingTextureRegistry::getAlbedoTexture() const {
    return mAlbedoTexture;
}

const Texture2D &DeferredShadingTextureRegistry::getPositionTexture() const {
    return mPositionTexture;
}

const Texture2D &DeferredShadingTextureRegistry::getNormalTexture() const {
    return mNormalTexture;
}

const Texture2D &DeferredShadingTextureRegistry::getMaterialDataTexture() const {
    return mMaterialDataTexture;
}

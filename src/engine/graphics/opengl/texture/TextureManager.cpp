#include "engine/graphics/opengl/texture/TextureManager.h"

TextureManager::TextureManager(): mMaxTextureSlots(-1) {
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &mMaxTextureSlots);
    mTextureSlots.resize(mMaxTextureSlots, nullptr);
    mReservedTextureSlots.resize(mMaxTextureSlots, false);
}

void TextureManager::begin() {

}

void TextureManager::addTexture(Texture &texture) {
    for (int i = 1; i < mTextureSlots.size(); ++i) {
        Texture* slot = mTextureSlots[i];
        if (slot != nullptr && slot->getId() == texture.getId()) {
            // Texture is already set to a slot
            mReservedTextureSlots[i] = true;
            return;
        }
    }
    for (int i = 1; i < mTextureSlots.size(); ++i) {
        if (mTextureSlots[i] == nullptr) {
            // There is a free texture slot
            mTextureSlots[i] = &texture;
            mReservedTextureSlots[i] = true;
            glActiveTexture(GL_TEXTURE0 + i);
            texture.bind();
            glActiveTexture(GL_TEXTURE0);
            return;
        }
    }
    // There are no free texture slots - need to re-use
    for (int i = 1; i < mTextureSlots.size(); ++i) {
        if (!mReservedTextureSlots[i]) {
            mReservedTextureSlots[i] = true;
            mTextureSlots[i] = &texture;
            glActiveTexture(GL_TEXTURE0 + i);
            texture.bind();
            glActiveTexture(GL_TEXTURE0);
            return;
        }
    }
}

void TextureManager::bindTexture(Texture& texture, const ShaderProgram& program, string uniform) {
    for (int i = 1; i < mTextureSlots.size(); ++i) {
        if (mTextureSlots[i] != nullptr && mTextureSlots[i]->getId() == texture.getId()) {
            program.setUniform(uniform, i);
        }
    }
}

void TextureManager::end() {
    for (int i = 1; i < mReservedTextureSlots.size(); ++i) {
        mReservedTextureSlots[i] = false;
    }
}
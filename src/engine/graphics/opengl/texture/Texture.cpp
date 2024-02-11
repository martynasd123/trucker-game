#include "engine/graphics/opengl/texture/Texture.h"

void Texture::bind() {
    glBindTexture(mTarget, mId);
}

void Texture::unbind() {
    glBindTexture(mTarget, 0);
}

GLuint Texture::getId() const {
    return mId;
}

Texture::Texture() {
    glGenTextures(1, &this->mId);
}

void Texture::setParameter(GLenum name, GLint value) {
    bind();
    glTexParameteri(mTarget, name, value);
    unbind();
}

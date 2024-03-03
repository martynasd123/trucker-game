#include "engine/graphics/opengl/texture/Texture.h"

void Texture::bind() const {
    glBindTexture(mTarget, *mId);
}

void Texture::unbind() const {
    glBindTexture(mTarget, 0);
}

GLuint Texture::getId() const {
    return *mId;
}

void destroyTexture(GLuint* tex) {
    glDeleteTextures(1, tex);
    delete tex;
}

Texture::Texture() {
    GLuint texId;
    glGenTextures(1, &texId);
    mId = std::shared_ptr<GLuint>(new GLuint(texId), destroyTexture);
}

void Texture::setParameter(GLenum name, GLint value) {
    bind();
    glTexParameteri(mTarget, name, value);
    unbind();
}

#include "engine/graphics/opengl/texture/Texture2D.h"

void Texture2D::setParameters() {
    setParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    setParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    setParameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
    setParameter(GL_TEXTURE_WRAP_T, GL_REPEAT);
}


Texture2D::Texture2D(GLint level, GLint internalformat, GLsizei width, GLsizei height, GLenum format,
                     GLenum type): Texture() {
    mTarget = GL_TEXTURE_2D;
    bind();
    glTexImage2D(mTarget, level, internalformat, width, height, 0, format, type, nullptr);
    unbind();
    setParameters();
}

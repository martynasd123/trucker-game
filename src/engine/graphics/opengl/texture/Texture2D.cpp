#include "engine/graphics/opengl/texture/Texture2D.h"

Texture2D::Texture2D(GLint level, GLint internalformat, GLsizei width, GLsizei height, GLenum format,
                     GLenum type): Texture() {
    mTarget = GL_TEXTURE_2D;
    bind();
    glTexImage2D(mTarget, level, internalformat, width, height, 0, format, type, nullptr);
    unbind();
}

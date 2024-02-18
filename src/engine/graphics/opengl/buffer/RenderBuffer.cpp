#include "engine/graphics/opengl/buffer/RenderBuffer.h"

void RenderBuffer::bind() {
    glBindRenderbuffer(GL_RENDERBUFFER, mId);
}

void RenderBuffer::unbind() {
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

RenderBuffer::RenderBuffer(GLenum internalFormat, unsigned int width, unsigned int height): mId(-1) {
    glGenRenderbuffers(1, &mId);
    bind();
    glRenderbufferStorage(GL_RENDERBUFFER, internalFormat, width, height);
    unbind();
}

GLuint RenderBuffer::getId() {
    return mId;
}

RenderBuffer::~RenderBuffer() {
    if (mId != -1) {
        glDeleteRenderbuffers(1, &mId);
    }
}

RenderBuffer::RenderBuffer(RenderBuffer&& other) noexcept {
    this->mId = other.mId;
    other.mId = -1;
}

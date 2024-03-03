#include "engine/graphics/opengl/buffer/RenderBuffer.h"

void RenderBuffer::bind() {
    glBindRenderbuffer(GL_RENDERBUFFER, *mId);
}

void RenderBuffer::unbind() {
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void destroyBuffer(GLuint* ptr) {
    glDeleteFramebuffers(1, ptr);
    delete ptr;
}

RenderBuffer::RenderBuffer(GLenum internalFormat, unsigned int width, unsigned int height) {
    GLuint id;
    glGenRenderbuffers(1, &id);
    this->mId = std::shared_ptr<GLuint>(new GLuint(id), destroyBuffer);
    bind();
    glRenderbufferStorage(GL_RENDERBUFFER, internalFormat, width, height);
    unbind();
}

GLuint RenderBuffer::getId() {
    return *mId;
}

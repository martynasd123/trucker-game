#include "engine/graphics/opengl/buffer/FrameBufferObject.h"

FrameBufferObject::FrameBufferObject() : mId(-1) {
    glGenFramebuffers(1, &mId);
}

void FrameBufferObject::bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, mId);
}

void FrameBufferObject::unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

FrameBufferObject::FrameBufferObject(FrameBufferObject &&other) noexcept {
    this->mId = other.mId;
    other.mId = -1;
}

#include "engine/graphics/opengl/buffer/GBuffer.h"
#include "engine/Globals.h"
#include "engine/graphics/opengl/util/GLUtils.h"

RenderBuffer initRenderBuffer(GLsizei width, GLsizei height) {
    return RenderBuffer(GL_DEPTH_COMPONENT, width, height);
}

void GBuffer::configureFrameBuffer() {
    GL_UTIL::checkError();
    bind();
    GL_UTIL::checkError();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                           mTextureRegistry.getAlbedoTexture().getId(), 0);
    GL_UTIL::checkError();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D,
                           mTextureRegistry.getNormalTexture().getId(), 0);
    GL_UTIL::checkError();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D,
                           mTextureRegistry.getPositionTexture().getId(), 0);
    GL_UTIL::checkError();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT3, GL_TEXTURE_2D,
                           mTextureRegistry.getMaterialDataTexture().getId(), 0);
    GL_UTIL::checkError();
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, mDepthAttachment.getId());
    GL_UTIL::checkError();

    unsigned int attachments[] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2,
                                  GL_COLOR_ATTACHMENT3};
    glDrawBuffers(4, attachments);
    GL_UTIL::checkError();

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        throw runtime_error("Could not set up G buffer");
    }

    unbind();
}

GBuffer::GBuffer(DeferredShadingTextureRegistry &textureRegistry, int width, int height) :
        FrameBufferObject(),
        mTextureRegistry(textureRegistry),
        mDepthAttachment(initRenderBuffer(width, height)) {
    configureFrameBuffer();
}

void GBuffer::updateDimensions(int width, int height) {
    GLuint oldFbo = mId;
    glGenFramebuffers(1, &mId);
    glDeleteFramebuffers(1, &oldFbo);
    GL_UTIL::checkError();
    mDepthAttachment = initRenderBuffer(width, height);
    GL_UTIL::checkError();
    configureFrameBuffer();
    GL_UTIL::checkError();
}

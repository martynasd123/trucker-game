#include "engine/graphics/opengl/buffer/GBuffer.h"
#include "engine/Globals.h"

RenderBuffer initRenderBuffer(GLsizei width, GLsizei height) {
    return RenderBuffer(GL_DEPTH_COMPONENT, width, height);
}

GBuffer::GBuffer(DeferredShadingTextureRegistry &textureRegistry) :
        FrameBufferObject(),
        mTextureRegistry(textureRegistry),
        mDepthAttachment(initRenderBuffer(WINDOW_WIDTH, WINDOW_HEIGHT)) {
    bind();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                           textureRegistry.getAlbedoTexture().getId(), 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D,
                           textureRegistry.getNormalTexture().getId(), 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D,
                           textureRegistry.getPositionTexture().getId(), 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT3, GL_TEXTURE_2D,
                           textureRegistry.getMaterialDataTexture().getId(), 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, mDepthAttachment.getId());

    unsigned int attachments[] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2,
                                  GL_COLOR_ATTACHMENT3};
    glDrawBuffers(4, attachments);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        throw runtime_error("Could not set up G buffer");
    }

    unbind();
}

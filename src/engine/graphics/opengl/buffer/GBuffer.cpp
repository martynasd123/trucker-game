#include "engine/graphics/opengl/buffer/GBuffer.h"
#include "engine/Globals.h"
#include "engine/graphics/opengl/util/GLUtils.h"

GBuffer::GBuffer(Texture2D &albedoTexture,
                 Texture2D &normalTexture,
                 Texture2D &positionTexture) : FrameBufferObject(),
                                               mColorAttachment(albedoTexture),
                                               mNormalAttachment(normalTexture),
                                               mPositionAttachment(positionTexture),
                                               mDepthAttachment(RenderBuffer(
                                                               GL_DEPTH_COMPONENT,
                                                               WINDOW_WIDTH,
                                                               WINDOW_HEIGHT)) {
    GL_UTIL::checkError();
    bind();
//    mColorAttachment.bind();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mColorAttachment.getId(), 0);
    GL_UTIL::checkError();

//    mNormalAttachment.bind();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, mNormalAttachment.getId(), 0);
    GL_UTIL::checkError();

//    mPositionAttachment.bind();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, mPositionAttachment.getId(), 0);
    GL_UTIL::checkError();

//    mDepthAttachment.bind();
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, mDepthAttachment.getId());
    GL_UTIL::checkError();

    unsigned int attachments[] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_DEPTH_ATTACHMENT};
    glDrawBuffers(2, attachments);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        throw runtime_error("Could not set up G buffer");
    }

    unbind();
}
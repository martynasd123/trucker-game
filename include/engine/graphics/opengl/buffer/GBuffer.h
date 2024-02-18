#ifndef TRUCKER_GAME_GBUFFER_H
#define TRUCKER_GAME_GBUFFER_H


#include "FrameBufferObject.h"
#include "engine/graphics/opengl/texture/Texture2D.h"
#include "RenderBuffer.h"

class GBuffer: public FrameBufferObject {
private:
    Texture2D& mColorAttachment;
    Texture2D& mNormalAttachment;
    Texture2D& mPositionAttachment;
    RenderBuffer mDepthAttachment;
public:
    GBuffer(Texture2D& albedoTexture, Texture2D& normalTexture, Texture2D& positionTexture);
};


#endif //TRUCKER_GAME_GBUFFER_H

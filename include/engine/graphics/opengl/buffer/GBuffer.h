#ifndef TRUCKER_GAME_GBUFFER_H
#define TRUCKER_GAME_GBUFFER_H

#include "FrameBufferObject.h"
#include "engine/graphics/opengl/texture/Texture2D.h"
#include "engine/graphics/opengl/texture/DeferredShadingTextureRegistry.h"
#include "RenderBuffer.h"

class GBuffer: public FrameBufferObject {
private:
    DeferredShadingTextureRegistry& mTextureRegistry;
    RenderBuffer mDepthAttachment;
    void configureFrameBuffer();
public:
    explicit GBuffer(DeferredShadingTextureRegistry& textureRegistry, int width, int height);
    void updateDimensions(int width, int height);
};


#endif //TRUCKER_GAME_GBUFFER_H

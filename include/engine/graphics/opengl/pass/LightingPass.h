#ifndef TRUCKER_GAME_LIGHTINGPASS_H
#define TRUCKER_GAME_LIGHTINGPASS_H

#include "RenderPass.h"
#include "../texture/Texture2D.h"
#include "../ObjectBasedBatch.h"
#include "../texture/TextureManager.h"

class LightingPass: public RenderPass {
protected:
    UniformBufferObject& mLightsUbo;
    Texture2D& mPositionTexture;
    Texture2D& mNormalTexture;
    Texture2D& mColorTexture;
    VertexBufferObject<Vector3f> mPositions;
    ElementBufferObject mEbo;
    VertexArrayObject mVao;
    MaterialHandlerRegistry& mHandlerRegistry;
    TextureManager& mTextureManager;
public:
    explicit LightingPass(UniformBufferObject& lightsUbo,
                          Texture2D& positionTexture,
                          Texture2D& normalTexture,
                          Texture2D& colorTexture,
                          MaterialHandlerRegistry& handlerRegistry,
                          TextureManager& textureManager);
    void draw();
};


#endif //TRUCKER_GAME_LIGHTINGPASS_H

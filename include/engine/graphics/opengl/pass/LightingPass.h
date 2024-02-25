#ifndef TRUCKER_GAME_LIGHTINGPASS_H
#define TRUCKER_GAME_LIGHTINGPASS_H

#include "RenderPass.h"
#include "../texture/Texture2D.h"
#include "../ObjectBasedBatch.h"
#include "../texture/TextureManager.h"

class LightingPass: public RenderPass {
protected:
    LightsUniformBufferObject<PointLight>& mPointLights;
    Texture2D& mPositionTexture;
    Texture2D& mNormalTexture;
    Texture2D& mColorTexture;
    Texture2D& mMaterialDataTexture;
    VertexBufferObject<Vector3f> mPositions;
    ElementBufferObject mEbo;
    VertexArrayObject mVao;
    MaterialHandlerRegistry& mHandlerRegistry;
    TextureManager& mTextureManager;
public:
    explicit LightingPass(LightsUniformBufferObject<PointLight>& lightsUbo,
                          Texture2D& positionTexture,
                          Texture2D& normalTexture,
                          Texture2D& colorTexture,
                          Texture2D& MaterialDataTexture,
                          MaterialHandlerRegistry& handlerRegistry,
                          TextureManager& textureManager);
    void draw();
};


#endif //TRUCKER_GAME_LIGHTINGPASS_H

#ifndef TRUCKER_GAME_LIGHTINGPASS_H
#define TRUCKER_GAME_LIGHTINGPASS_H

#include "RenderPass.h"
#include "../texture/Texture2D.h"
#include "../texture/DeferredShadingTextureRegistry.h"
#include "../ObjectBasedBatch.h"
#include "../texture/TextureManager.h"

class LightingPass: public RenderPass {
protected:
    GLBufferArrayList<PointLight>& mPointLights;
    DeferredShadingTextureRegistry& mTextureRegistry;
    GLBufferArray<Vector3f, TIGHTLY_PACKED> mPositions;
    GLBufferArray<unsigned int, TIGHTLY_PACKED> mEbo;
    VertexArrayObject mVao;
    MaterialHandlerRegistry& mHandlerRegistry;
    TextureManager& mTextureManager;
public:
    explicit LightingPass(GLBufferArrayList<PointLight>& lightsUbo,
                          DeferredShadingTextureRegistry& textureRegistry,
                          MaterialHandlerRegistry& handlerRegistry,
                          TextureManager& textureManager,
                          int width, int height);
    void draw();

    void updateDimensions(int width, int height);
};


#endif //TRUCKER_GAME_LIGHTINGPASS_H

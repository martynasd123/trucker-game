#ifndef TRUCKER_GAME_GEOMETRYPASS_H
#define TRUCKER_GAME_GEOMETRYPASS_H

#include "RenderPass.h"
#include "engine/Globals.h"
#include "engine/graphics/opengl/Camera.h"
#include "engine/graphics/opengl/texture/Texture2D.h"
#include "engine/graphics/opengl/texture/DeferredShadingTextureRegistry.h"
#include "engine/graphics/opengl/buffer/GBuffer.h"
#include "engine/graphics/opengl/ObjectBasedBatch.h"
#include "engine/graphics/opengl/shader/ShaderProgram.h"
#include "engine/graphics/opengl/buffer/std140.h"

class GeometryPass: public RenderPass {
protected:
    unique_ptr<GBuffer> mGBuffer;
    Camera& mCam;
public:
    GeometryPass(DeferredShadingTextureRegistry& textureRegistry, Camera& cam, int width, int height);
    void draw(ObjectBasedBatch& batch);

    void updateDimensions(int width, int height);
};


#endif //TRUCKER_GAME_GEOMETRYPASS_H
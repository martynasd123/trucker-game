#ifndef TRUCKER_GAME_GEOMETRYPASS_H
#define TRUCKER_GAME_GEOMETRYPASS_H

#include "RenderPass.h"
#include "engine/Globals.h"
#include "engine/graphics/opengl/Camera.h"
#include "engine/graphics/opengl/texture/Texture2D.h"
#include "engine/graphics/opengl/buffer/GBuffer.h"
#include "engine/graphics/opengl/ObjectBasedBatch.h"
#include "engine/graphics/opengl/shader/ShaderProgram.h"
#include "engine/graphics/opengl/buffer/BufferObject.h"
#include "engine/graphics/opengl/buffer/std140.h"

class GeometryPass: public RenderPass {
protected:
    GBuffer* mGBuffer;
    Camera& mCam;
public:
    GeometryPass(Texture2D& albedoTexture, Texture2D& normalTexture, Texture2D& positionTexture, Texture2D& MaterialDataTexture, Camera& cam);
    void draw(ObjectBasedBatch& batch);
};


#endif //TRUCKER_GAME_GEOMETRYPASS_H

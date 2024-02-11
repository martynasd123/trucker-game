#ifndef TRUCKER_GAME_GEOMETRYPASS_H
#define TRUCKER_GAME_GEOMETRYPASS_H

#include "RenderPass.h"
#include "engine/Globals.h"
#include "engine/graphics/opengl/texture/Texture2D.h"
#include "engine/graphics/opengl/ObjectBasedBatch.h"
#include "engine/graphics/opengl/shader/ShaderProgram.h"

class GeometryPass: public RenderPass {
private:
    Texture2D mTexAlbedo = Texture2D(0, GL_RGB, WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGB, GL_UNSIGNED_BYTE);
    ShaderProgram* mShaderProgram{};
public:
    GeometryPass();
    void draw(ObjectBasedBatch* batch);
};


#endif //TRUCKER_GAME_GEOMETRYPASS_H

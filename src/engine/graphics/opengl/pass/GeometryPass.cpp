#include "engine/graphics/opengl/pass/GeometryPass.h"
#include "engine/Globals.h"
#include "engine/resource/resolver/TextResourceResolver.h"
#include "engine/graphics/opengl/shader/VertexShader.h"
#include "engine/graphics/opengl/shader/FragmentShader.h"
#include "common/math/Matrix4f.h"

GeometryPass::GeometryPass(Texture2D &albedoTexture, Texture2D &normalTexture, Texture2D &positionTexture) :
        mGBuffer(new GBuffer(albedoTexture, normalTexture, positionTexture)) {
    GL_UTIL::checkError();
}

static float x = 0.0f;
static float y = 0.0f;

double degreesToRadians(double degrees) {
    return degrees * M_PI / 180.0;
}

void GeometryPass::draw(ObjectBasedBatch *batch) {

    auto transform = batch->getTransform();

    Matrix4f model = Matrix4f::scaling(transform.scale)
                     * Matrix4f::rotationY(degreesToRadians(y += 1.0f))
                     * Matrix4f::rotationX(degreesToRadians(30))
                     * Matrix4f::translation(transform.position);
    Matrix4f view = Matrix4f::IDENTITY;
    Matrix4f projection = Matrix4f::ortho(10.0f, -10.0f, 10.0f, -10.0f, 10.0f, -10.0f);

//    mShaderProgram->setUniform("u_transform", model * view * projection);
//    mShaderProgram->bindUBO("ub_materials", 0);

//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    Matrix4f worldToClip = view * projection;

    mGBuffer->bind();

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Matrix4f combined = model * view * projection;

    for (const auto &materialBatch: batch->getMaterialBatches()) {
        const ShaderProgram &shaderProgram = *materialBatch->getMaterialHandler().getShaderProgramForPass(GEOMETRY_PASS);

        shaderProgram.use();
        shaderProgram.setUniform("u_model_to_world", model);
        shaderProgram.setUniform("u_world_to_clip", worldToClip);
        shaderProgram.bindUBO("ub_materials", MATERIAL_DATA_BINDING_POINT);
        materialBatch->draw();

    }
}

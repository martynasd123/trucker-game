#include "engine/graphics/opengl/pass/GeometryPass.h"
#include "engine/Globals.h"
#include "engine/resource/resolver/TextResourceResolver.h"
#include "engine/graphics/opengl/shader/VertexShader.h"
#include "engine/graphics/opengl/shader/FragmentShader.h"
#include "common/math/Matrix4f.h"

GeometryPass::GeometryPass(Texture2D &albedoTexture, Texture2D &normalTexture, Texture2D &positionTexture, Texture2D &MaterialDataTexture, Camera& cam) :
        mGBuffer(new GBuffer(albedoTexture, normalTexture, positionTexture, MaterialDataTexture)),
         mCam(cam){
    GL_UTIL::checkError();
}

static float x = 0.0f;
static float y = 0.0f;

double degreesToRadians(double degrees) {
    return degrees * M_PI / 180.0;
}

void GeometryPass::draw(ObjectBasedBatch& batch) {

    auto transform = batch.getTransform();


    Matrix4f model = Matrix4f::scaling(transform.scale)
                     * Matrix4f::rotationY(degreesToRadians(y += 1.0f))
                     * Matrix4f::rotationX(degreesToRadians(30.0))
                     * Matrix4f::translation(transform.position);

    Matrix4f modelView = mCam.getView() * model;

    Matrix4f transformation = mCam.getProjection() * modelView;

    mGBuffer->bind();


    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (const auto &materialBatch: batch.getMaterialBatches()) {
        const ShaderProgram &shaderProgram = *materialBatch->getMaterialHandler().getShaderProgramForPass(GEOMETRY_PASS);

        shaderProgram.use();
        shaderProgram.setUniform("u_transformation", transformation);
        shaderProgram.setUniform("u_modelView", modelView);
        shaderProgram.bindUBO("ub_materials", MATERIAL_DATA_BINDING_POINT);
        materialBatch->draw();

    }
}

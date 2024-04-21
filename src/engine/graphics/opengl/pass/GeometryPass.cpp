#include "engine/graphics/opengl/pass/GeometryPass.h"
#include "engine/graphics/opengl/shader/VertexShader.h"
#include "common/math/Matrix4f.h"

GeometryPass::GeometryPass(DeferredShadingTextureRegistry &textureRegistry, Camera &cam, int width, int height) :
        mGBuffer(make_unique<GBuffer>(textureRegistry, width, height)),
        mCam(cam) {
}

void GeometryPass::draw(ObjectBasedBatch &batch) {

    auto transform = batch.getTransform();

    Matrix4f modelView = mCam.getView() * batch.getModel();

    Matrix4f transformation = mCam.getProjection() * modelView;

    mGBuffer->bind();

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (const auto &materialBatch: batch.getMaterialBatches()) {
        const ShaderProgram &shaderProgram = *materialBatch->getMaterialHandler().getShaderProgramForPass(
                GEOMETRY_PASS);

        shaderProgram.use();
        shaderProgram.setUniform("u_transformation", transformation);
        shaderProgram.setUniform("u_modelView", modelView);
        shaderProgram.bindUBO("ub_materials", MATERIAL_DATA_BINDING_POINT);
        materialBatch->draw();

    }
}

void GeometryPass::updateDimensions(int width, int height) {
    mGBuffer->updateDimensions(width, height);
}

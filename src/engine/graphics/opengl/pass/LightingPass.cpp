#include "engine/graphics/opengl/pass/LightingPass.h"

#include "vector"

LightingPass::LightingPass(GLBufferArrayList<PointLight> &lightsUbo,
                           DeferredShadingTextureRegistry &textureRegistry,
                           MaterialHandlerRegistry &handlerRegistry,
                           TextureManager &textureManager,
                           int width, int height) : mPointLights(lightsUbo),
                                                             mPositions(ARRAY_BUFFER, 4, STATIC_DRAW),
                                                             mVao(VertexArrayObject()),
                                                             mHandlerRegistry(handlerRegistry),
                                                             mTextureManager(textureManager),
                                                             mEbo(ELEMENT_BUFFER, 6, STATIC_DRAW),
                                                             mTextureRegistry(textureRegistry) {
    vector<Vector3f> positions;
    positions.emplace_back(-1.0f, -1.0f, 0.0f);
    positions.emplace_back(-1.0f, 1.0f, 0.0f);
    positions.emplace_back(1.0f, 1.0f, 0.0f);
    positions.emplace_back(1.0f, -1.0f, 0.0f);
    mPositions.setData(positions.begin(), positions.end(), 0);

    vector<unsigned int> indices({0, 1, 2, 0, 3, 2});
    mEbo.setData(indices.begin(), indices.end(), 0);

    mPositions.attachToVertexArrayObject(0, mVao);
    mEbo.attachToVertexArrayObjectAsElementBuffer(mVao);
}

void LightingPass::draw() {
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    mPointLights.bindAsUniformBufferObject(POINT_LIGHT_DATA_BINDING_POINT);

    mTextureManager.begin();
    mTextureManager.addTexture(mTextureRegistry.getPositionTexture());
    mTextureManager.addTexture(mTextureRegistry.getNormalTexture());
    mTextureManager.addTexture(mTextureRegistry.getAlbedoTexture());
    mTextureManager.addTexture(mTextureRegistry.getMaterialDataTexture());

    mVao.bind();
    for (const auto &handler: mHandlerRegistry.getHandlers()) {
        const ShaderProgram &program = *handler->getShaderProgramForPass(LIGHTING_PASS);
        program.bindUBO("ub_lights", POINT_LIGHT_DATA_BINDING_POINT);

        program.use();
        program.setUniform("u_numLights", (unsigned int) mPointLights.size());

        mTextureManager.bindTexture(mTextureRegistry.getPositionTexture(), program, "u_gPosition");
        mTextureManager.bindTexture(mTextureRegistry.getNormalTexture(), program, "u_gNormal");
        mTextureManager.bindTexture(mTextureRegistry.getAlbedoTexture(), program, "u_gAlbedo");
        mTextureManager.bindTexture(mTextureRegistry.getMaterialDataTexture(), program, "u_gMaterial");

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    }
    mVao.unbind();

    mTextureManager.end();
}

void LightingPass::updateDimensions(int width, int height) {
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glViewport(0, 0, width, height);
}

#include "engine/graphics/opengl/pass/LightingPass.h"
#include "engine/Globals.h"

#include "vector"

LightingPass::LightingPass(LightsUniformBufferObject<PointLight> &lightsUbo,
                           Texture2D &positionTexture,
                           Texture2D &normalTexture,
                           Texture2D &colorTexture,
                           Texture2D &MaterialDataTexture,
                           MaterialHandlerRegistry &handlerRegistry,
                           TextureManager &textureManager) : mPointLights(lightsUbo),
                                                              mPositions(VertexBufferObject<Vector3f>(4)),
                                                              mVao(VertexArrayObject()),
                                                              mPositionTexture(positionTexture),
                                                              mNormalTexture(normalTexture),
                                                              mColorTexture(colorTexture),
                                                              mHandlerRegistry(handlerRegistry),
                                                              mTextureManager(textureManager),
                                                              mMaterialDataTexture(MaterialDataTexture),
                                                              mEbo(6){
    vector<Vector3f> positions;
    positions.emplace_back(-1.0f, -1.0f, 0.0f);
    positions.emplace_back(-1.0f, 1.0f, 0.0f);
    positions.emplace_back(1.0f, 1.0f, 0.0f);
    positions.emplace_back(1.0f, -1.0f, 0.0f);
    mPositions.setData(positions.begin(), positions.end(), 0);
    vector<unsigned int> indices({0, 1, 2, 0, 3, 2});
    mEbo.setData(indices.begin(), indices.end(), 0);
    mVao.addVertexAttribute(0, &mPositions);
    mVao.addElementBuffer(&mEbo);
}

void LightingPass::draw() {
    GL_UTIL::checkError();
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

    glViewport(0, 0, VIEWPORT_WIDTH, VIEWPORT_HEIGHT);

    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GL_UTIL::checkError();

    mPointLights.bindToPoint(POINT_LIGHT_DATA_BINDING_POINT);

    mTextureManager.begin();
    mTextureManager.addTexture(mPositionTexture);
    mTextureManager.addTexture(mNormalTexture);
    mTextureManager.addTexture(mColorTexture);
    mTextureManager.addTexture(mMaterialDataTexture);

    mVao.bind();
    for (const auto &handler: mHandlerRegistry.getHandlers()) {
        const ShaderProgram &program = *handler->getShaderProgramForPass(LIGHTING_PASS);
        program.bindUBO("ub_lights", POINT_LIGHT_DATA_BINDING_POINT);

        program.use();
        program.setUniform("u_numLights", mPointLights.getNumLights());

        GL_UTIL::checkError();
        mTextureManager.bindTexture(mPositionTexture, program, "u_gPosition");
        mTextureManager.bindTexture(mNormalTexture, program, "u_gNormal");
        mTextureManager.bindTexture(mColorTexture, program, "u_gAlbedo");
        mTextureManager.bindTexture(mMaterialDataTexture, program, "u_gMaterial");
        GL_UTIL::checkError();

        glDrawElements(GL_TRIANGLES, 6,  GL_UNSIGNED_INT, nullptr);
        GL_UTIL::checkError();
    }
    mVao.unbind();

    mTextureManager.end();
}

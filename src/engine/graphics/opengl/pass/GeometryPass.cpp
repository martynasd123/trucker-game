#include "engine/graphics/opengl/pass/GeometryPass.h"
#include "engine/Globals.h"
#include "engine/resource/resolver/TextResourceResolver.h"
#include "engine/graphics/opengl/shader/VertexShader.h"
#include "engine/graphics/opengl/shader/FragmentShader.h"


GeometryPass::GeometryPass() {
    auto handle = resourceManager->acquireHandle<TextResource>("assets/shaders/geometry/monochromatic/vertex.glsl");
    VertexShader vertexShader = VertexShader(resourceManager->getResource<TextResource>(handle)->text);
    resourceManager->releaseResource(handle);
    handle = resourceManager->acquireHandle<TextResource>("assets/shaders/geometry/monochromatic/fragment.glsl");
    FragmentShader fragmentShader = FragmentShader(resourceManager->getResource<TextResource>(handle)->text);
    resourceManager->releaseResource(handle);

    mShaderProgram = new ShaderProgram;

    mShaderProgram->addShader(&vertexShader);
    mShaderProgram->addShader(&fragmentShader);
    mShaderProgram->link();
}

void GeometryPass::draw(ObjectBasedBatch *batch) {
    mShaderProgram->use();
    auto transform = batch->getTransform();


    for (const auto &materialBatch: batch->getMaterialBatches()) {
        materialBatch->draw();
    }
}

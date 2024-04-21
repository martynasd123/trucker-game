#ifndef TRUCKER_GAME_MATERIALHANDLERBASE_H
#define TRUCKER_GAME_MATERIALHANDLERBASE_H

#include <utility>

#include "engine/graphics/opengl/material/MaterialHandler.h"
#include "engine/resource/manager/ResourceManager.h"
#include "engine/graphics/opengl/shader/VertexShader.h"
#include "engine/graphics/opengl/shader/FragmentShader.h"

class MaterialHandlerBase: public MaterialHandler {
private:
    ResourceManager& mResManager;
protected:
    PassId mOverriddenPasses;
    unordered_map<PassId, ShaderProgram> mShaderPrograms;

    void registerShader(PassId pass, ResourcePath vertexShader, ResourcePath fragmentShader) {
        auto handle = mResManager.acquireHandle<TextResource>(std::move(vertexShader));
        auto vertexShaderObj = VertexShader(mResManager.getResource<TextResource>(handle)->text);
        mResManager.releaseResource(handle);

        handle = mResManager.acquireHandle<TextResource>(std::move(fragmentShader));
        auto fragmentShaderObj = FragmentShader(mResManager.getResource<TextResource>(handle)->text);
        mResManager.releaseResource(handle);

        auto program = ShaderProgram();
        program.addShader(&vertexShaderObj);
        program.addShader(&fragmentShaderObj);
        program.link();

        mShaderPrograms.emplace(pass, std::move(program));
        mOverriddenPasses|=pass;
    }

    explicit MaterialHandlerBase(ResourceManager& resManager): mResManager(resManager) {}

public:

    PassId getOverriddenPasses() const override {
        return mOverriddenPasses;
    }

    [[nodiscard]] const ShaderProgram *getShaderProgramForPass(PassId passId) const override {
        if (!mShaderPrograms.contains(passId)) {
            throw invalid_argument(string("Material ") + getMaterialTypeName() + " does not define shader for pass " +
                                           passId.to_string());
        }
        return &mShaderPrograms.at(passId);
    }
};


#endif //TRUCKER_GAME_MATERIALHANDLERBASE_H
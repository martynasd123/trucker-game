#ifndef TRUCKER_GAME_MATERIALHANDLER_H
#define TRUCKER_GAME_MATERIALHANDLER_H

#include <memory>
#include "engine/graphics/opengl/shader/ShaderProgram.h"
#include "engine/graphics/opengl/buffer/BufferObject.h"
#include "engine/graphics/opengl/Definitions.h"
#include "common/render/Material.h"

using namespace std;

class MaterialHandler {
public:

    /**
     * Returns a bitset, such that performing logical AND with a pass id determines whether this material overrides
     * that pass.
     */
    virtual PassId getOverriddenPasses() const = 0;

    /**
     * @return the material type name of material to be rendered
     */
    virtual std::string getMaterialTypeName() const = 0;

    /**
     * @return The size of one material object, as written in the UBO.
     */
    virtual unsigned int getUBOMaterialSize() const = 0;

    /**
     * Write material data to uniform buffer object. Material data must be written in given order.
     */
    virtual void writeToUniformBuffer(vector<Material*> materials, int offset, BufferObjectBase& buff) const = 0;

    /**
     * Returns a shader that is to be used for the given pass, or nullptr if the pass is not supported by this
     * material.
     * @return Reference to shader program.
     */
    virtual const ShaderProgram* getShaderProgramForPass(PassId passId) const = 0;

    virtual ~MaterialHandler() {

    }
};


#endif //TRUCKER_GAME_MATERIALHANDLER_H

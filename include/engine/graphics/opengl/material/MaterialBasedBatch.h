#ifndef TRUCKER_GAME_MATERIALBASEDBATCH_H
#define TRUCKER_GAME_MATERIALBASEDBATCH_H

#include "MaterialBasedBatch.h"
#include "common/render/Mesh.h"
#include "engine/graphics/opengl/buffer/GLBuffer.h"
#include "engine/graphics/opengl/VertexArrayObject.h"
#include "engine/graphics/opengl/material/MaterialHandler.h"

#include <vector>

using namespace std;

using Vector3fVertexBufferObject = GLBufferArray<Vector3f, TIGHTLY_PACKED>;
using Vector2fVertexBufferObject = GLBufferArray<Vector2f, TIGHTLY_PACKED>;
using UnsignedIntVertexBufferObject = GLBufferArray<unsigned int, TIGHTLY_PACKED>;

class MaterialBasedBatchBase {
protected:
    /**
     * Holds position of each vertex
     */
    unique_ptr<Vector3fVertexBufferObject> mPositions;

    /**
     * Holds normal vector of each vertex
     */
    unique_ptr<Vector3fVertexBufferObject> mNormals;

    /**
     * Holds UV coordinate of each vector
     */
    unique_ptr<Vector2fVertexBufferObject> mUVCoords;

    /**
     * Holds the index of material associated with vertex.
     */
    unique_ptr<UnsignedIntVertexBufferObject> mMaterialIndices;

    /**
     * Holds batch vertex indices
     */
    unique_ptr<UnsignedIntVertexBufferObject> mElementBuffer;

    /**
     * The vertex array object for this batch
     */
    unique_ptr<VertexArrayObject> mVao = nullptr;

    /**
     * Holds material indices that reference materials in the mesh object
     */
    vector<unsigned int> mMaterialMappings;

    /**
     * Material handler, associated with the material type
     */
    const MaterialHandler &mMaterialHandler;

    /**
     * Number of vertex indices for this batch
     */
    int mNumElements;

    explicit MaterialBasedBatchBase(const Mesh& mesh, const MaterialHandler &materialHandler);

public:

    /**
     * Draw this batch with the current shader and fbo configuration.
     */
    virtual void draw() = 0;

    [[nodiscard]] const MaterialHandler &getMaterialHandler() const;

    virtual ~MaterialBasedBatchBase() = default;
};

template<typename MaterialType>
class MaterialBasedBatch : public MaterialBasedBatchBase {
protected:

    /**
     * Holds material data in an array, which is indexed by one of the vertex attributes
     */
    unique_ptr<GLBufferArray<MaterialType, STD140>> mUbo;

    /**
     * Holds the material data
     */
    vector<MaterialType> mMaterialData;

public:
    MaterialBasedBatch(const Mesh& mesh, const MaterialHandler &materialHandler)
            : MaterialBasedBatchBase(mesh, materialHandler) {
        for (const auto &mapping: mMaterialMappings) {
            mMaterialData.emplace_back(*dynamic_pointer_cast<MaterialType>(mesh.materials[mapping]).get());
        }

        mUbo = make_unique<GLBufferArray<MaterialType, STD140>>(UNIFORM_BUFFER, mMaterialData.size(), STATIC_DRAW);
        mUbo->setData(mMaterialData.begin(), mMaterialData.end(), 0);
    }

    void draw() override {
        mUbo->bindAsUniformBufferObject(MATERIAL_DATA_BINDING_POINT);
        mVao->bind();
        glDrawElements(GL_TRIANGLES, mNumElements, GL_UNSIGNED_INT, nullptr);
        mVao->unbind();
    }
};

#endif //TRUCKER_GAME_MATERIALBASEDBATCH_H

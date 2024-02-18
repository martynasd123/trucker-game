#ifndef TRUCKER_GAME_MATERIALBASEDBATCH_H
#define TRUCKER_GAME_MATERIALBASEDBATCH_H

#include "MaterialBasedBatch.h"
#include "common/render/Mesh.h"
#include "engine/graphics/opengl/buffer/BufferObject.h"
#include "engine/graphics/opengl/VertexArrayObject.h"
#include "engine/graphics/opengl/material/MaterialHandler.h"

#include <vector>

using namespace std;

class MaterialBasedBatch {
private:
    // Holds position of each vertex
    VertexBufferObject<Vector3f>* mPositions = nullptr;
    // Holds normal vector of each vertex
    VertexBufferObject<Vector3f>* mNormals = nullptr;
    // Holds UV coordinate of each vector
    VertexBufferObject<Vector2f>* mUVCoords = nullptr;
    // Holds the index of material associate with vertex.
    VertexBufferObject<unsigned int>* mMaterialIndices = nullptr;
    ElementBufferObject* mElementBuffer = nullptr;
    UniformBufferObject* mUbo = nullptr;
    VertexArrayObject* mVao = nullptr;
    const MaterialHandler& mMaterialHandler;
    int mNumElements;
public:
    explicit MaterialBasedBatch(Mesh* mesh, const MaterialHandler& materialHandler);
    void draw();

    const MaterialHandler &getMaterialHandler() const;

    virtual ~MaterialBasedBatch();
};

#endif //TRUCKER_GAME_MATERIALBASEDBATCH_H

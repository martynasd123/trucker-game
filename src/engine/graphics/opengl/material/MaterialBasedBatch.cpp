#include "engine/graphics/opengl/material/MaterialBasedBatch.h"
#include "common/util/Triple.h"
#include "common/util/HashableArray.h"

using namespace std;

MaterialBasedBatchBase::MaterialBasedBatchBase(const Mesh& mesh, const MaterialHandler &materialHandler) :
        mMaterialHandler(materialHandler) {
    vector<Vector3f> positions;
    vector<Vector3f> normals;
    vector<Vector2f> uv;
    vector<unsigned int> materialIndices;

    vector<unsigned int> indices;
    vector<shared_ptr<Material>> materials;

    unordered_map<array<int, 4>, int> vertMap;

    for (int i = 0; i < mesh.materialMappings.size(); ++i) {
        if (mesh.materials[i]->getTypeString() != "bp-monochromatic") {
            continue;
        }
        for (const auto &groupMapping: mesh.materialMappings[i].groups) {
            auto primitives = mesh.getGroupByName(groupMapping)->primitives;
            for (const auto &primitiveIndex: primitives) {
                for (const auto &vert: mesh.primitives[primitiveIndex].vertices) {
                    array<int, 4> vertData = {vert.positionIndex, vert.normalIndex, vert.uvIndex, i};
                    if (vertMap.contains(vertData)) {
                        indices.push_back(vertMap[vertData]);
                    } else {
                        vertMap[vertData] = positions.size();
                        indices.push_back(positions.size());

                        materialIndices.push_back(materials.size());
                        positions.push_back(mesh.positions[vert.positionIndex]);
                        normals.push_back(mesh.normals[vert.normalIndex]);
                        uv.push_back(mesh.uvCoordinates[vert.uvIndex]);
                    }
                }
            }
        }
        materials.push_back(mesh.materials[i]);
        mMaterialMappings.push_back(i);
    }

    mPositions = make_unique<Vector3fVertexBufferObject>(ARRAY_BUFFER, positions.size(), STATIC_DRAW);
    mPositions->setData(positions.begin(), positions.end(), 0);

    mNormals = make_unique<Vector3fVertexBufferObject>(ARRAY_BUFFER, normals.size(), STATIC_DRAW);
    mNormals->setData(normals.begin(), normals.end(), 0);

    mUVCoords = make_unique<Vector2fVertexBufferObject>(ARRAY_BUFFER, uv.size(), STATIC_DRAW);
    mUVCoords->setData(uv.begin(), uv.end(), 0);

    mMaterialIndices = make_unique<UnsignedIntVertexBufferObject>(ARRAY_BUFFER, materialIndices.size(), STATIC_DRAW);
    mMaterialIndices->setData(materialIndices.begin(), materialIndices.end(), 0);

    mElementBuffer = make_unique<UnsignedIntVertexBufferObject>(ELEMENT_BUFFER, indices.size(), STATIC_DRAW);
    mElementBuffer->setData(indices.begin(), indices.end(), 0);

    mVao = make_unique<VertexArrayObject>();
    mPositions->attachToVertexArrayObject(0, *mVao);
    mNormals->attachToVertexArrayObject(1, *mVao);
    mUVCoords->attachToVertexArrayObject(2, *mVao);
    mMaterialIndices->attachToVertexArrayObject(3, *mVao);
    mElementBuffer->attachToVertexArrayObjectAsElementBuffer(*mVao);

    mNumElements = indices.size();
}

const MaterialHandler &MaterialBasedBatchBase::getMaterialHandler() const {
    return mMaterialHandler;
}

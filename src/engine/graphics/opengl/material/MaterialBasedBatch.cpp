#include "engine/graphics/opengl/material/MaterialBasedBatch.h"
#include "common/util/Triple.h"
#include "common/util/HashableArray.h"

#include <iostream>

using namespace std;

MaterialBasedBatch::MaterialBasedBatch(Mesh *mesh, const MaterialHandler& materialHandler): mMaterialHandler(materialHandler) {
    vector<Vector3f> positions;
    vector<Vector3f> normals;
    vector<Vector2f> uv;
    vector<unsigned int> materialIndices;

    vector<unsigned int> indices;
    vector<Material*> materials;

    unordered_map<array<int, 4>, int> vertMap;

    for (int i = 0; i < mesh->materialMappings.size(); ++i) {
        if (mesh->materials[i]->getTypeString() != "bp-monochromatic") {
            continue;
        }
        for (const auto &groupMapping: mesh->materialMappings[i].groups) {
            auto primitives = mesh->getGroupByName(groupMapping)->primitives;
            for (const auto &primitiveIndex: primitives) {
                for (const auto &vert: mesh->primitives[primitiveIndex].vertices) {
                    array<int, 4> vertData = {vert.positionIndex, vert.normalIndex, vert.uvIndex, i};
                    if (vertMap.contains(vertData)) {
                        indices.push_back(vertMap[vertData]);
                    } else {
                        vertMap[vertData] = positions.size();
                        indices.push_back(positions.size());

                        materialIndices.push_back(materials.size());
                        positions.push_back(mesh->positions[vert.positionIndex]);
                        normals.push_back(mesh->normals[vert.normalIndex]);
                        uv.push_back(mesh->uvCoordinates[vert.uvIndex]);
                    }
                }
            }
        }
        materials.push_back(mesh->materials[i]);
    }

    mPositions = new VertexBufferObject<Vector3f>(positions.size());
    mPositions->setData(positions.begin(), positions.end(), 0);

    mNormals = new VertexBufferObject<Vector3f>(normals.size());
    mNormals->setData(normals.begin(), normals.end(), 0);

    mUVCoords = new VertexBufferObject<Vector2f>(uv.size());
    mUVCoords->setData(uv.begin(), uv.end(), 0);

    mMaterialIndices = new VertexBufferObject<unsigned int>(materialIndices.size());
    mMaterialIndices->setData(materialIndices.begin(), materialIndices.end(), 0);

    mElementBuffer = new ElementBufferObject(indices.size());
    mElementBuffer->setData(indices.begin(), indices.end(), 0);

    mVao = new VertexArrayObject;
    mVao->addVertexAttribute(0, mPositions);
    mVao->addVertexAttribute(1, mNormals);
    mVao->addVertexAttribute(2, mUVCoords);
    mVao->addVertexAttribute(3, mMaterialIndices);
    mVao->addElementBuffer(mElementBuffer);

    mUbo = new UniformBufferObject(materialHandler.getUBOMaterialSize() * materials.size());
    materialHandler.writeToUniformBuffer(materials, 0, *dynamic_cast<BufferObjectBase*>(mUbo));
    mNumElements = indices.size();
}

void MaterialBasedBatch::draw() {
    mUbo->bindToPoint(MATERIAL_DATA_BINDING_POINT);
    mVao->bind();
    glDrawElements(GL_TRIANGLES, mNumElements, GL_UNSIGNED_INT, nullptr);
    mVao->unbind();
}

MaterialBasedBatch::~MaterialBasedBatch() {
    delete mPositions;
    delete mNormals;
    delete mUVCoords;
    delete mElementBuffer;
    delete mVao;
    delete mUbo;
}

const MaterialHandler &MaterialBasedBatch::getMaterialHandler() const {
    return mMaterialHandler;
}

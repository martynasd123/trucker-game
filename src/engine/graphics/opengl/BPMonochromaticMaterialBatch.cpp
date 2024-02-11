#include "engine/graphics/opengl/BPMonochromaticMaterialBatch.h"
#include "common/util/Triple.h"

using namespace std;

BPMonochromaticMaterialBatch::BPMonochromaticMaterialBatch(Mesh *mesh) {
    vector<Vector3f> positions;
    vector<Vector3f> normals;
    vector<Vector2f> uv;

    vector<int> indices;

    unordered_map<Triple<int, int, int>, int> vertMap;

    int materialIndex = 0;
    for (int i = 0; i < mesh->materialMappings.size(); ++i) {
        if (mesh->materials[i]->getTypeString() != "bp-monochromatic") {
            continue;
        }
        for (const auto &groupMapping: mesh->materialMappings[i].groups) {
            auto primitives = mesh->getGroupByName(groupMapping)->primitives;
            for (const auto &primitiveIndex: primitives) {
                for (const auto &vert: mesh->primitives[primitiveIndex].vertices) {
                    Triple<int, int, int> triple = {vert.positionIndex, vert.normalIndex, vert.uvIndex};
                    if (vertMap.contains(triple)) {
                        indices.push_back(vertMap[triple]);
                    } else {
                        vertMap[triple] = positions.size();
                        positions.push_back(mesh->positions[vert.positionIndex]);
                        normals.push_back(mesh->normals[vert.normalIndex]);
                        uv.push_back(mesh->uvCoordinates[vert.uvIndex]);
                    }
                }
            }
        }
    }
    mPositions = new VertexBufferObject<Vector3f>(positions.size());
    mPositions->setData(positions.begin(), positions.end(), 0);

    mNormals = new VertexBufferObject<Vector3f>(normals.size());
    mNormals->setData(normals.begin(), normals.end(), 0);

    mUVCoords = new VertexBufferObject<Vector2f>(uv.size());
    mUVCoords->setData(uv.begin(), uv.end(), 0);

    mElementBuffer = new VertexBufferObject<int>(indices.size(), GL_ELEMENT_ARRAY_BUFFER);
    mElementBuffer->setData(indices.begin(), indices.end(), 0);

    mVao = new VertexArrayObject;
    mVao->addVertexAttribute(0, mPositions);
    mVao->addVertexAttribute(1, mNormals);
    mVao->addVertexAttribute(2, mUVCoords);
    mVao->addElementBuffer(mElementBuffer);

    mNumElements = indices.size();
}

void BPMonochromaticMaterialBatch::draw() {
    mVao->bind();
    glDrawElements(GL_TRIANGLES, mNumElements, GL_UNSIGNED_INT, nullptr);
    mVao->unbind();
}

BPMonochromaticMaterialBatch::~BPMonochromaticMaterialBatch() {
    delete mPositions;
    delete mNormals;
    delete mUVCoords;
    delete mElementBuffer;
    delete mVao;
}

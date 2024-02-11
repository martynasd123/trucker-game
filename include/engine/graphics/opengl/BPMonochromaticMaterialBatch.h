#ifndef TRUCKER_GAME_BPMONOCHROMATICMATERIALBATCH_H
#define TRUCKER_GAME_BPMONOCHROMATICMATERIALBATCH_H

#include "MaterialBasedBatch.h"
#include "common/render/Mesh.h"
#include "buffer/VertexBufferObject.h"
#include "VertexArrayObject.h"

#include <vector>

using namespace std;

class BPMonochromaticMaterialBatch: public MaterialBasedBatch {
private:
    VertexBufferObject<Vector3f>* mPositions = nullptr;
    VertexBufferObject<Vector3f>* mNormals = nullptr;
    VertexBufferObject<Vector2f>* mUVCoords = nullptr;
    VertexBufferObject<int>* mElementBuffer = nullptr;
    VertexArrayObject* mVao = nullptr;
    int mNumElements;
public:
    explicit BPMonochromaticMaterialBatch(Mesh* mesh);
    void draw() override;

    virtual ~BPMonochromaticMaterialBatch();
};


#endif //TRUCKER_GAME_BPMONOCHROMATICMATERIALBATCH_H

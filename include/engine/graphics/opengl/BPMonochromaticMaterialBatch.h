#ifndef TRUCKER_GAME_BPMONOCHROMATICMATERIALBATCH_H
#define TRUCKER_GAME_BPMONOCHROMATICMATERIALBATCH_H

#include "MaterialBasedBatch.h"
#include "common/render/Mesh.h"
#include "buffer/VertexBufferObject3f.h"
#include "buffer/VertexBufferObject2f.h"

#include <vector>

using namespace std;

class BPMonochromaticMaterialBatch: public MaterialBasedBatch {
private:
    VertexBufferObject3f mPositions;
    VertexBufferObject3f mNormals;
    VertexBufferObject2f mUVCoords;
public:
    explicit BPMonochromaticMaterialBatch(Mesh* mesh);
    void draw() override;
};


#endif //TRUCKER_GAME_BPMONOCHROMATICMATERIALBATCH_H

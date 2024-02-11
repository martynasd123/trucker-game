#ifndef TRUCKER_GAME_OBJECTBASEDBATCH_H
#define TRUCKER_GAME_OBJECTBASEDBATCH_H

#include "common/render/Mesh.h"
#include "common/math/Transform.h"
#include "Batch.h"
#include "MaterialBasedBatch.h"

class ObjectBasedBatch: public Batch {
private:
    Transform mTransform;
    vector<MaterialBasedBatch*> mMaterialBatches;

    void createMaterialBasedBatch(string materialType, Mesh* mesh);
public:
    ObjectBasedBatch(Mesh* mesh, Transform transform);

    void setTransform(const Transform transform);

    const Transform &getTransform() const;

    const vector<MaterialBasedBatch *> &getMaterialBatches() const;
};


#endif //TRUCKER_GAME_OBJECTBASEDBATCH_H

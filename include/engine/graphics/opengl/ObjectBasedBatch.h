#ifndef TRUCKER_GAME_OBJECTBASEDBATCH_H
#define TRUCKER_GAME_OBJECTBASEDBATCH_H

#include "common/render/Mesh.h"
#include "common/math/Transform.h"
#include "Batch.h"
#include "engine/graphics/opengl/material/MaterialBasedBatch.h"
#include "engine/graphics/opengl/material/MaterialHandlerRegistry.h"

class ObjectBasedBatch: public Batch {
private:
    Transform mTransform;
    vector<shared_ptr<MaterialBasedBatchBase>> mMaterialBatches;
    MaterialHandlerRegistry& mHandlerRegistry;

    void createMaterialBasedBatch(const string& materialType, const Mesh& mesh);
public:
    ObjectBasedBatch(const Mesh& mesh, Transform transform, MaterialHandlerRegistry& registry);

    void setTransform(const Transform transform);

    const Transform &getTransform() const;

    const vector<shared_ptr<MaterialBasedBatchBase>> &getMaterialBatches() const;


};


#endif //TRUCKER_GAME_OBJECTBASEDBATCH_H

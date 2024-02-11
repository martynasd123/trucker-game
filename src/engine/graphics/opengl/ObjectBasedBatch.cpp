#include "engine/graphics/opengl/ObjectBasedBatch.h"
#include "engine/graphics/opengl/BPMonochromaticMaterialBatch.h"

#include <vector>

using namespace std;

void ObjectBasedBatch::createMaterialBasedBatch(string materialType, Mesh* mesh) {
    if (materialType == "bp-monochromatic") {
        auto materialBatch = new BPMonochromaticMaterialBatch(mesh);
        mMaterialBatches.push_back(dynamic_cast<MaterialBasedBatch*>(materialBatch));
    } else if (materialType == "bp-textured") {
        // TODO
    } else {
        throw runtime_error("Invalid material type encountered: " + materialType);
    }
}

ObjectBasedBatch::ObjectBasedBatch(Mesh *mesh, Transform transform): mTransform(transform) {
    vector<Material*> materials(mesh->materials);

    // Sort materials by type
    sort(materials.begin(), materials.end(), [](Material* mat1, Material* mat2) {
        return mat1->getTypeString() > mat2->getTypeString();
    });

    string lastMaterialType;
    for (const auto &mat: materials) {
        if (mat->getTypeString() != lastMaterialType) {
            createMaterialBasedBatch(mat->getTypeString(), mesh);
            lastMaterialType = mat->getTypeString();
        }
    }
}

void ObjectBasedBatch::setTransform(const Transform transform) {
    this->mTransform = transform;
}

const Transform &ObjectBasedBatch::getTransform() const {
    return mTransform;
}

const vector<MaterialBasedBatch *> &ObjectBasedBatch::getMaterialBatches() const {
    return mMaterialBatches;
}

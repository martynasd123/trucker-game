#include "engine/graphics/opengl/ObjectBasedBatch.h"

#include <utility>
#include <vector>

using namespace std;

void ObjectBasedBatch::createMaterialBasedBatch(const string &materialType, const Mesh &mesh) {
    if (materialType == "bp-monochromatic") {
        auto materialBatch = make_shared<MaterialBasedBatch<BPMonochromaticMaterial>>(mesh, mHandlerRegistry.getHandler(
                materialType));
        mMaterialBatches.push_back(materialBatch);
    } else if (materialType == "bp-textured") {
        // TODO
    } else {
        throw runtime_error("Invalid material type encountered: " + materialType);
    }
}

ObjectBasedBatch::ObjectBasedBatch(const Mesh &mesh, Transform transform, MaterialHandlerRegistry &registry)
        : mTransform(std::move(transform)),mHandlerRegistry(registry),
          mModel(transform.computeModelMatrix()){
    vector<shared_ptr<Material>> materials(mesh.materials);

    // Sort materials by type
    sort(materials.begin(), materials.end(), [](const shared_ptr<Material> &mat1, const shared_ptr<Material> &mat2) {
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
    this->mModel = transform.computeModelMatrix();
}

const Transform &ObjectBasedBatch::getTransform() const {
    return mTransform;
}

const vector<shared_ptr<MaterialBasedBatchBase>> &ObjectBasedBatch::getMaterialBatches() const {
    return mMaterialBatches;
}

const Matrix4f &ObjectBasedBatch::getModel() const {
    return mModel;
}

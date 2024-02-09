#include "engine/graphics/opengl/BPMonochromaticMaterialBatch.h"

void BPMonochromaticMaterialBatch::draw() {

}

BPMonochromaticMaterialBatch::BPMonochromaticMaterialBatch(Mesh *mesh) {
    vector<Vector3f> positions;

    int materialIndex = 0;
    for (int i = 0; i < mesh->materialMappings.size(); ++i) {
        if (mesh->materials[i]->getTypeString() != "bp-monochromatic") {
            continue;
        }
        for (const auto &groupMapping: mesh->materialMappings[i].groups) {
            auto primitives = mesh->getGroupByName(groupMapping)->primitives;
            
        }
    }
}

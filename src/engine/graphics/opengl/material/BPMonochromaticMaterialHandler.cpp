#include "engine/graphics/opengl/material/BPMonochromaticMaterialHandler.h"
#include "engine/graphics/opengl/buffer/std140.h"

#include <iostream>
#include <cstddef>

std::string BPMonochromaticMaterialHandler::getMaterialTypeName() const {
    return "bp-monochromatic";
}

//void BPMonochromaticMaterialHandler::writeToUniformBuffer(vector<BPMonochromaticMaterial> materials,
//                                                         int offset, BufferObjectBase& buff) {
//    std140BPMonoChromaticMaterial materialArray[materials.size()];
//    for (int i = 0; i < materials.size(); ++i) {
//        cout << "Material " << i << endl;
//        cout << "color: " << materials[i].color.getX() << " " << materials[i].color.getY() << " " << materials[i].color.getZ() << endl;
//        cout << "specular " << materials[i].specular.getX() << " " << materials[i].specular.getY() << " " << materials[i].specular.getZ() << endl;
//        materialArray[i] = std140BPMonoChromaticMaterial(&materials[i]);
//        cout << endl;
//    }
//    cout << "Alignments: " << endl;
//    unsigned int numBytes = sizeof(std140BPMonoChromaticMaterial) * materials.size();
//    cout << "specular: " << (int)offsetof(struct std140BPMonoChromaticMaterial, specular) << endl;
//    cout << "ambient: " << (int)offsetof(struct std140BPMonoChromaticMaterial, ambient) << endl;
//    cout << "color: " << (int)offsetof(struct std140BPMonoChromaticMaterial, color) << endl;
//    cout << "diffuse: " << (int)offsetof(struct std140BPMonoChromaticMaterial, diffuse) << endl;
//    cout << "shininess: " << (int)offsetof(struct std140BPMonoChromaticMaterial, shininess) << endl;
//
//    buff.setData((char*) &materialArray, numBytes, offset);
//}

void BPMonochromaticMaterialHandler::writeToUniformBuffer(vector<BPMonochromaticMaterial> materials,
                                                         int offset, BufferObjectBase& buff) const {
    char arr[materials.size() * 48];
    float* curr = (float*) &arr[0];
    for (int i = 0; i < materials.size(); ++i) {
        curr = (float*) (&arr[0] + 48 * i);
        BPMonochromaticMaterial& mat = materials[i];
        *curr = mat.specular.getX();
        curr++;
        *curr = mat.specular.getY();
        curr++;
        *curr = mat.specular.getZ();
        curr++;
        curr++;
        *curr = mat.color.getX();
        curr++;
        *curr = mat.color.getY();
        curr++;
        *curr = mat.color.getZ();
        curr++;
        *curr = mat.ambient;
        curr++;
        *curr = mat.diffuse;
        curr++;
        *curr = mat.shininess;
    }

    buff.setData((char*) arr, sizeof(arr), offset);
}

BPMonochromaticMaterialHandler::BPMonochromaticMaterialHandler(ResourceManager &resManager) : MaterialHandlerBase(resManager) {
    registerShader(GEOMETRY_PASS, "assets/shaders/geometry/monochromatic/vertex.glsl", "assets/shaders/geometry/monochromatic/fragment.glsl");
    registerShader(LIGHTING_PASS, "assets/shaders/lighting/monochromatic/vertex.glsl", "assets/shaders/lighting/monochromatic/fragment.glsl");
}

unsigned int BPMonochromaticMaterialHandler::getUBOMaterialSize() const {
    return sizeof(std140BPMonoChromaticMaterial);
}


#include "engine/graphics/opengl/material/BPMonochromaticMaterialHandler.h"
#include "engine/graphics/opengl/buffer/std140.h"

std::string BPMonochromaticMaterialHandler::getMaterialTypeName() const {
    return "bp-monochromatic";
}


void BPMonochromaticMaterialHandler::writeToUniformBuffer(vector<BPMonochromaticMaterial> materials,
                                                         int offset, BufferObjectBase& buff) const {

    struct std140Material {
        float specularX;
        float specularY;
        float specularZ;
        float pad0;
        float colorX;
        float colorY;
        float colorZ;
        float ambient;
        float diffuse;
        float shininess;
        float pad1;
        float pad2;
    };

    std140Material arr[materials.size()];
    for (int i = 0; i < materials.size(); ++i) {
        BPMonochromaticMaterial& mat = materials[i];
        auto std140mat = std140Material();
        std140mat.specularX = mat.specular.getX();
        std140mat.specularY = mat.specular.getY();
        std140mat.specularZ = mat.specular.getZ();
        std140mat.colorX = mat.color.getX();
        std140mat.colorY = mat.color.getY();
        std140mat.colorZ = mat.color.getZ();
        std140mat.ambient = mat.ambient;
        std140mat.diffuse = mat.diffuse;
        std140mat.shininess = mat.shininess;
        arr[i] = std140mat;
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


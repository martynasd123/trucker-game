#include "engine/graphics/opengl/material/BPMonochromaticMaterialHandler.h"

std::string BPMonochromaticMaterialHandler::getMaterialTypeName() const {
    return "bp-monochromatic";
}

BPMonochromaticMaterialHandler::BPMonochromaticMaterialHandler(ResourceManager &resManager) : MaterialHandlerBase(resManager) {
    registerShader(GEOMETRY_PASS, "assets/shaders/geometry/monochromatic/vertex.glsl", "assets/shaders/geometry/monochromatic/fragment.glsl");
    registerShader(LIGHTING_PASS, "assets/shaders/lighting/monochromatic/vertex.glsl", "assets/shaders/lighting/monochromatic/fragment.glsl");
}


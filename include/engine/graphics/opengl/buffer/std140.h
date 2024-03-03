#ifndef TRUCKER_GAME_STD140_H
#define TRUCKER_GAME_STD140_H

#include "common/render/Light.h"

struct std140BPMonoChromaticMaterial {
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

struct std140PointLight {
    float ambientX;
    float ambientY;
    float ambientZ;
    float quadratic;
    float diffuseX;
    float diffuseY;
    float diffuseZ;
    float linear;
    float specularX;
    float specularY;
    float specularZ;
    float constant;
    float positionX;
    float positionY;
    float positionZ;
    float pad0;

    explicit std140PointLight(const PointLight &light) :
            ambientX(light.ambient.getX()),
            ambientY(light.ambient.getY()),
            ambientZ(light.ambient.getZ()),
            diffuseX(light.diffuse.getX()),
            diffuseY(light.diffuse.getY()),
            diffuseZ(light.diffuse.getZ()),
            specularX(light.specular.getX()),
            specularY(light.specular.getY()),
            specularZ(light.specular.getZ()),
            positionX(light.position.getX()),
            positionY(light.position.getY()),
            positionZ(light.position.getZ()),
            constant(light.constant),
            quadratic(light.quadratic),
            linear(light.linear){}

    std140PointLight() {}
};

#endif //TRUCKER_GAME_STD140_H

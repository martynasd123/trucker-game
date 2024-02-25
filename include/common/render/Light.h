#ifndef TRUCKER_GAME_LIGHT_H
#define TRUCKER_GAME_LIGHT_H

#include "common/math/Vector3f.h"

struct Light {
    enum LightType {
        POINT_LIGHT,
        DIRECTIONAL_LIGHT,
        NULL_LIGHT
    };

    LightType type;
    Vector3f ambient;
    Vector3f diffuse;
    Vector3f specular;


    Light(LightType pType, const Vector3f ambient, const Vector3f diffuse, const Vector3f specular) : type(pType),
                                                                                             ambient(ambient),
                                                                                             specular(specular),
                                                                                             diffuse(diffuse){}

    Light() : type(NULL_LIGHT), ambient(), diffuse(), specular() {}
};

struct PointLight : public Light {
    Vector3f position;
    // Attenuation parameters
    float constant;
    float linear;
    float quadratic;

    PointLight(const Vector3f ambient, const Vector3f diffuse, const Vector3f specular,
               const Vector3f position, float constant, float linear, float quadratic) : Light(POINT_LIGHT, ambient,
                                                                                                diffuse,
                                                                                                specular),
                                                                                          position(position),
                                                                                          constant(constant),
                                                                                          linear(linear),
                                                                                          quadratic(quadratic) {}
};

#endif //TRUCKER_GAME_LIGHT_H

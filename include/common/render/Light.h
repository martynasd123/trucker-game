#ifndef TRUCKER_GAME_LIGHT_H
#define TRUCKER_GAME_LIGHT_H

#include "common/math/Vector3f.h"

struct Light {
    enum LightType{
        POINT_LIGHT,
        DIRECTIONAL_LIGHT,
        NULL_LIGHT
    };

    LightType type;
    float intensity;
    Vector3f color;


    Light(LightType pType, float pIntensity, const Vector3f &pColor) : type(pType), intensity(pIntensity), color(pColor) {}

    Light(): type(NULL_LIGHT), intensity(0.0f), color(Vector3f(0.0f, 0.0f, 0.0f)) {}
};

struct PointLight: public Light {
    Vector3f position;

    PointLight(float intensity, const Vector3f &color, const Vector3f &position) : Light(POINT_LIGHT, intensity, color),
                                                                                   position(position) {}
};

struct DirectionalLight: public Light {
    Vector3f heading;

    DirectionalLight(float intensity, const Vector3f &color, const Vector3f &heading) : Light(DIRECTIONAL_LIGHT, intensity, color),
                                                                                        heading(heading) {}
};

static const Light NULL_LIGHT = Light();

#endif //TRUCKER_GAME_LIGHT_H

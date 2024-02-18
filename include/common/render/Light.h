#ifndef TRUCKER_GAME_LIGHT_H
#define TRUCKER_GAME_LIGHT_H

#include "common/math/Vector3f.h"

struct Light {
    float intensity;
    Vector3f color;

    Light(float intensity, const Vector3f &color) : intensity(intensity), color(color) {}
};

struct PointLight: public Light {
    Vector3f position;

    PointLight(float intensity, const Vector3f &color, const Vector3f &position) : Light(intensity, color),
                                                                                   position(position) {}
};

struct DirectionalLight: public Light {
    Vector3f heading;

    DirectionalLight(float intensity, const Vector3f &color, const Vector3f &heading) : Light(intensity, color),
                                                                                        heading(heading) {}
};

#endif //TRUCKER_GAME_LIGHT_H

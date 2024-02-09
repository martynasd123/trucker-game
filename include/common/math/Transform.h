#ifndef TRUCKER_GAME_TRANSFORM_H
#define TRUCKER_GAME_TRANSFORM_H

#include "Quarternion.h"
#include "Vector3f.h"

struct Transform {
    Quaternion rotation;
    Vector3f position;
    Vector3f scale;
};

#endif //TRUCKER_GAME_TRANSFORM_H

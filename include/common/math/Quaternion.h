#ifndef TRUCKER_GAME_QUATERNION_H
#define TRUCKER_GAME_QUATERNION_H

#include "common/math/Matrix4f.h"

class Quaternion {
    float x, y, z, w;
public:
    static const Quaternion IDENTITY;
public:
    Quaternion(float x, float y, float z, float w);

    /**
     * Constructs an instance of Quaternion from euler angles
     */
    static Quaternion fromEuler(float x, float y, float z);

    /**
     * Return a new quaternion rotated about x axis
     */
    Quaternion rotateX(float rad);

    Quaternion operator*(const Quaternion& q) const;

    Matrix4f toRotationMatrix() const;
};

#endif //TRUCKER_GAME_QUATERNION_H

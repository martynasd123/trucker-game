#ifndef TRUCKER_GAME_VECTOR4F_H
#define TRUCKER_GAME_VECTOR4F_H

#include "common/math/Matrix4f.h"
#include "common/math/Vector3f.h"

class Vector4f {
private:
    float _x, _y, _z, _w;
public:
    Vector4f() : _x(0.0f), _y(0.0f), _z(0.0f), _w(0.0f) {}

    Vector4f(Vector3f vec, float w) : _x(vec.getX()), _y(vec.getY()), _z(vec.getZ()), _w(w) {}

    Vector4f(float x, float y, float z, float w) : _x(x), _y(y), _z(z), _w(w) {}

    [[nodiscard]] float getX() const;

    [[nodiscard]] float getY() const;

    [[nodiscard]] float getZ() const;

    [[nodiscard]] float getW() const;

    Vector4f operator*(const Matrix4f& matrix) const;

    [[nodiscard]] Vector3f xyz() const;
};


#endif //TRUCKER_GAME_VECTOR4F_H

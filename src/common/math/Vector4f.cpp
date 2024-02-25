#include "common/math/Vector4f.h"

float Vector4f::getX() const {
    return _x;
}

float Vector4f::getY() const {
    return _y;
}

float Vector4f::getZ() const {
    return _z;
}

float Vector4f::getW() const {
    return _w;
}

Vector4f Vector4f::operator*(const Matrix4f& matrix) const {
    return {
        matrix.at(0, 0) * getX() + matrix.at(0, 1) * getY() + matrix.at(0, 2) * getZ() + matrix.at(0, 3) * getW(),
        matrix.at(1, 0) * getX() + matrix.at(1, 1) * getY() + matrix.at(1, 2) * getZ() + matrix.at(1, 3) * getW(),
        matrix.at(2, 0) * getX() + matrix.at(2, 1) * getY() + matrix.at(2, 2) * getZ() + matrix.at(2, 3) * getW(),
        matrix.at(3, 0) * getX() + matrix.at(3, 1) * getY() + matrix.at(3, 2) * getZ() + matrix.at(3, 3) * getW()
    };
};

Vector3f Vector4f::xyz() const {
    return {_x, _y, _z};
}

#include "common/math/Vector3f.h"

float Vector3f::getX() const {
    return _x;
}

float Vector3f::getY() const {
    return _y;
}

float Vector3f::getZ() const {
    return _z;
}

Vector3f &Vector3f::operator=(const Vector3f &other) {
    this->_x = other.getX();
    this->_y = other.getY();
    this->_z = other.getZ();
    return *this;
}

Vector3f Vector3f::operator/(const float divisor) const {
    return {getX() / divisor, getY() / divisor, getZ() / divisor};
}

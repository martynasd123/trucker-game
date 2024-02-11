#include "common/math/Quarternion.h"

const Quaternion Quaternion::IDENTITY = Quaternion(0.0f, 0.0f, 0.0f, 1.0f);

Quaternion::Quaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
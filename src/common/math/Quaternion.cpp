#include <math.h>
#include "common/math/Quaternion.h"

const Quaternion Quaternion::IDENTITY = Quaternion(0.0f, 0.0f, 0.0f, 1.0f);

Quaternion::Quaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

Quaternion Quaternion::fromEuler(float pX, float pY, float pZ)
{
    float c1 = cosf(pY / 2.0f);
    float c2 = cosf(pX / 2.0f);
    float c3 = cosf(pZ / 2.0f);
    float s1 = sinf(pY / 2.0f);
    float s2 = sinf(pX / 2.0f);
    float s3 = sinf(pZ / 2.0f);
    return {s1 * s2 * c3 + c1 * c2 * s3, s1 * c2 * c3 + c1 * s2 * s3, c1 * s2 * c3 - s1 * c2 * s3,
            c1 * c2 * c3 - s1 * s2 * s3};
}

Quaternion Quaternion::rotateX(float rad)
{
    return *this * fromEuler(rad, 0.0f, 0.0f);
}

Quaternion Quaternion::operator*(const Quaternion &q) const
{
    return Quaternion(
        w * q.x + x * q.w + y * q.z - z * q.y,
        w * q.y - x * q.z + y * q.w + z * q.x,
        w * q.z + x * q.y - y * q.x + z * q.w,
        w * q.w - x * q.x - y * q.y - z * q.z);
}

Matrix4f Quaternion::toRotationMatrix() const
{
    return Matrix4f({1.0f - 2.0f * powf(y, 2.0f) - 2.0f * powf(z, 2.0f), 2.0f * x * y - 2.0f * z * w,
                     2.0f * x * z + 2.0f * y * w, 0.0f,
                     2.0f * x * y + 2.0f * z * w, 1.0f - 2.0f * powf(x, 2.0f) - 2.0f * powf(z, 2.0f),
                     2.0f * y * z - 2.0f * x * w, 0.0f,
                     2.0f * x * z - 2.0f * y * w, 2.0f * y * z + 2.0f * x * w,
                     1.0f - 2.0f * powf(x, 2.0f) - 2.0f * powf(y, 2.0f), 0.0f,
                     0.0f, 0.0f, 0.0f, 1.0f});
}
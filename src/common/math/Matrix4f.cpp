#include "common/math/Matrix4f.h"
#include <cmath>


const Matrix4f Matrix4f::IDENTITY = Matrix4f({
                                                     1.0f, 0.0f, 0.0f, 0.0f,
                                                     0.0f, 1.0f, 0.0f, 0.0f,
                                                     0.0f, 0.0f, 1.0f, 0.0f,
                                                     0.0f, 0.0f, 0.0f, 1.0f
                                             });

float Matrix4f::at(int row, int col) const {
    return (*_values)[row * 4 + col];
}

const float *Matrix4f::array() const {
    return _values->data();
}

Matrix4f Matrix4f::ortho(float right, float left, float top, float bottom, float far, float near) {
    return Matrix4f({
                            2.0f / (right - left), 0.0f, 0.0f, -(right + left) / (right - left),
                            0.0f, 2.0f / (top - bottom), 0.0f, -(top + bottom) / (top - bottom),
                            0.0f, 0.0f, 2.0f / (far - near), (far + near) / (far - near),
                            0.0f, 0.0f, 0.0f, 1.0f
                    });
}


Matrix4f Matrix4f::perspective(float right, float left, float top, float bottom, float far, float near) {
    return Matrix4f({
                            2.0f * near / (right - left), 0.0f, (right + left) / (left - right), 0.0f,
                            0.0f, 2.0f * near / (top - bottom), (top + bottom) / (bottom - top), 0.0f,
                            0.0f, 0.0f, (far + near) / (far - near), -2.0f * far * near / (far - near),
                            0.0f, 0.0f, 1.0f, 0.0f
                    });
}

Matrix4f Matrix4f::perspective(float fov, float aspect, float far, float near) {
    float top = tanf(fov / 2.0f) * near;
    float bottom = -top;
    float right = top * aspect;
    float left = -right;
    return perspective(right, left, top, bottom, far, near);
}

Matrix4f Matrix4f::scaling(float sx, float sy, float sz) {
    return Matrix4f({
                            sx, 0.0f, 0.0f, 0.0f,
                            0.0f, sy, 0.0f, 0.0f,
                            0.0f, 0.0f, sz, 0.0f,
                            0.0f, 0.0f, 0.0f, 1.0f
                    });
}


Matrix4f Matrix4f::scaling(Vector3f vec) {
    return scaling(vec.getX(), vec.getY(), vec.getZ());
}

Matrix4f Matrix4f::translation(float tx, float ty, float tz) {
    return Matrix4f({
                            1.0f, 0.0f, 0.0f, tx,
                            0.0f, 1.0f, 0.0f, ty,
                            0.0f, 0.0f, 1.0f, tz,
                            0.0f, 0.0f, 0.0f, 1.0f
                    });
}

Matrix4f Matrix4f::translation(Vector3f position) {
    return translation(position.getX(), position.getY(), position.getZ());
}

Matrix4f Matrix4f::rotationX(float rx) {
    return Matrix4f({
                            1.0f, 0.0f, 0.0f, 0.0f,
                            0.0f, cos(rx), -sin(rx), 0.0f,
                            0.0f, sin(rx), cos(rx), 0.0f,
                            0.0f, 0.0f, 0.0f, 1.0f
                    });
}

Matrix4f Matrix4f::rotationY(float ry) {
    return Matrix4f({
                            cos(ry), 0.0f, sin(ry), 0.0f,
                            0.0f, 1.0f, 0.0f, 0.0f,
                            -sin(ry), 0.0f, cos(ry), 0.0f,
                            0.0f, 0.0f, 0.0f, 1.0f
                    });
}

Matrix4f Matrix4f::operator*(const Matrix4f &other) const {
    float newMatrix[16];
    for (int col = 0; col < 4; col++) {
        for (int row = 0; row < 4; row++) {
            newMatrix[row * 4 + col] = at(row, 0) * other.at(0, col)
                                       + at(row, 1) * other.at(1, col)
                                       + at(row, 2) * other.at(2, col)
                                       + at(row, 3) * other.at(3, col);
        }
    }
    return Matrix4f(newMatrix);
}

Matrix4f Matrix4f::transposed() const {
    float newMatrix[16];
    for (int col = 0; col < 4; col++) {
        for (int row = 0; row < 4; row++) {
            newMatrix[row * 4 + col] = at(col, row);
        }
    }
    return Matrix4f(newMatrix);
}

template<size_t N>
Matrix4f::Matrix4f(const float (&values)[N]) : _values(make_shared<std::array<float, 16>>(std::array<float, 16>())) {
    std::copy(begin(values), begin(values) + 16, _values->begin());
}

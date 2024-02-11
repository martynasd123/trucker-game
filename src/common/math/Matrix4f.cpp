#include "common/math/Matrix4f.h"

const Matrix4f Matrix4f::IDENTITY = Matrix4f({
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
});

float Matrix4f::at(int row, int col) {
    return _values[row * 4 + col];
}

const float *Matrix4f::array() const {
    return _values;
}

Matrix4f Matrix4f::ortho(float right, float left, float top, float bottom, float far, float near) {
    return Matrix4f({
            2.0f / (right - left), 0.0f, 0.0f, - (right + left) / (right - left),
            0.0f, 2.0f / (top - bottom), 0.0f, - (top + bottom) / (top - bottom),
            0.0f, 0.0f, 2.0f / (far - near), (far + near) / (far - near),
            0.0f, 0.0f, 0.0f, 1.0f
    });
}

Matrix4f Matrix4f::scaling(float sx, float sy, float sz) {
   return Matrix4f({
       sx, 0.0f, 0.0f, 0.0f,
       0.0f, sy, 0.0f, 0.0f,
       0.0f, 0.0f, sz, 0.0f,
       0.0f, 0.0f, 0.0f, 1.0f
   });
}

Matrix4f Matrix4f::translation(float tx, float ty, float tz) {
   return Matrix4f({
       1.0f, 0.0f, 0.0f, tx,
       0.0f, 1.0f, 0.0f, ty,
       0.0f, 0.0f, 1.0f, tz,
       0.0f, 0.0f, 0.0f, 1.0f
   });
}

Matrix4f Matrix4f::operator*(Matrix4f other) {
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

Matrix4f Matrix4f::transposed() {
    float newMatrix[16];
    for (int col = 0; col < 4; col++) {
        for (int row = 0; row < 4; row++) {
            newMatrix[row * 4 + col] = at(col, row);
        }
    }
    return Matrix4f(newMatrix);
}

template<size_t N>
Matrix4f::Matrix4f(const float (&values)[N]): _values(new float[16]) {
    static_assert(N == 16, "Incorrectly sized array passed to constructor of Matrix4f");
    std::copy(values, values + 16, _values);
}

Matrix4f::Matrix4f(Matrix4f const &other): _values(new float[16]) {
    std::copy(other._values, other._values + 16, _values);
}

Matrix4f::Matrix4f(Matrix4f &&other) noexcept : _values(other._values)  {
    other._values = nullptr;
}

Matrix4f::~Matrix4f() {
    delete[] _values;
}

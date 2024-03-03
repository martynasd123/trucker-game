#ifndef TRUCKER_GAME_MATRIX4F_H
#define TRUCKER_GAME_MATRIX4F_H

#include "common/math/Vector3f.h"
#include <array>
#include <iostream>

using namespace std;

/**
 * Representation of 4x4 matrix. Where relevant, assuming left-handed coordinate system with Y axis pointing up.
 * This class is immutable - any operations involving it return a new object.
 */
class Matrix4f {
    shared_ptr<array<float, 16>> _values;
public:
    static const Matrix4f IDENTITY;

    /**
     * Generates an orthographic projection matrix.
     * @return Orthographic projection matrix
     */
    static Matrix4f ortho(float right, float left, float top, float bottom, float far, float near);

    /**
     * Generates an perspective projection matrix.
     * @return Perspective projection matrix
     */
    static Matrix4f perspective(float right, float left, float top, float bottom, float far, float near);

    /**
     * Generates a perspective projection matrix
     * @param fov Field of view (in radians)
     * @param aspect Aspect ratio (width/height)
     * @param far The far plane
     * @param near The near plane
     * @return A perspective projection matrix
     */
    static Matrix4f perspective(float fov, float aspect, float far, float near);

    /**
     * Generates a scaling transformation matrix
     * @return Scaling transformation matrix
     */
    static Matrix4f scaling(float sx, float sy, float sz);

    static Matrix4f scaling(Vector3f vec);

    /**
     * Generates a translation transformation matrix
     * @return Translation transformation matrix
     */
    static Matrix4f translation(float sx, float sy, float sz);

    static Matrix4f translation(Vector3f vec);

    static Matrix4f rotationX(float rx);

    static Matrix4f rotationY(float rY);

    /**
     * Constructs a new matrix object
     * @param values Array of values, in row-major order
     */
    template<size_t N>
    explicit Matrix4f(const float (&values)[N]);

    /**
     * Returns the value at a given row and column
     * @param row The row index (starting at 0)
     * @param col The column index (starting at 0)
     */
    [[nodiscard]] float at(int row, int col) const;

    /**
     * @return Raw pointer to array of values, in row-major order.
     */
    [[nodiscard]] const float *array() const;

    /**
     * @return A new matrix that is the transposed version of this one
     */
    [[nodiscard]] Matrix4f transposed() const;

    void toString() const {
        string acc;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                acc += to_string(at(i, j));
                acc += " ";
            }
            acc += "\n";
        }
    }

    /**
     * Performs matrix multiplication
     * @param other The matrix to multiply by
     * @return Matrix resulting from multiplication
     */
    Matrix4f operator*(const Matrix4f& other) const;
};

#endif //TRUCKER_GAME_MATRIX4F_H

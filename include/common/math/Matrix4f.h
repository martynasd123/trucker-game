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
    float *_values;
public:
    static const Matrix4f IDENTITY;

    /**
     * Generates an orthographic projection matrix.
     * @return Orthographic projection matrix
     */
    static const Matrix4f ortho(float right, float left, float top, float bottom, float far, float near);

    /**
     * Generates an perspective projection matrix.
     * @return Perspective projection matrix
     */
    static const Matrix4f perspective(float right, float left, float top, float bottom, float far, float near);

    static const Matrix4f perspective(float fov, float aspect, float far, float near);

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
    Matrix4f(const float (&values)[N]);

    /**
     * Returns the value at a given row and column
     * @param row The row index (starting at 0)
     * @param col The column index (starting at 0)
     */
    float at(int row, int col) const;

    /**
     * @return Raw pointer to array of values, in row-major order.
     */
    const float *array() const;

    /**
     * @return A new matrix that is the transposed version of this one
     */
    Matrix4f transposed() const;

    void print() const {
        cout << at(0, 0) << " " << at(0, 1) << " " << at(0, 2) << " " << at(0, 3) << endl;
        cout << at(1, 0) << " " << at(1, 1) << " " << at(1, 2) << " " << at(1, 3) << endl;
        cout << at(2, 0) << " " << at(2, 1) << " " << at(2, 2) << " " << at(2, 3) << endl;
        cout << at(3, 0) << " " << at(3, 1) << " " << at(3, 2) << " " << at(3, 3) << endl;
    }

    /**
     * Performs matrix multiplication
     * @param other The matrix to multiply by
     * @return Matrix resulting from multiplication
     */
    Matrix4f operator*(const Matrix4f other) const;

    Matrix4f(const Matrix4f &other);

    Matrix4f(Matrix4f &&other) noexcept;

    Matrix4f &operator=(const Matrix4f &other);

    ~Matrix4f();
};

#endif //TRUCKER_GAME_MATRIX4F_H

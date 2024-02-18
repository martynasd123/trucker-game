#ifndef TRUCKER_GAME_STD140_H
#define TRUCKER_GAME_STD140_H

#include <cstdint>
#include "common/math/Matrix4f.h"
#include "common/render/Material.h"

struct alignas(4) std140float {
    float x;

    explicit std140float(float x) : x(x) {}
    std140float() {}
};

struct alignas(8) std140Vec2 {
    std140float x, y;
};

struct alignas(16) std140Vec3 {
    std140float x, y, z;

    std140Vec3() {}
    std140Vec3(Vector3f &vec) : x(vec.getX()), y(vec.getY()), z(vec.getZ()) {}
};

struct alignas(16) std140Vec4 {
    std140float _x, _y, _z, _w;

    std140Vec4(float x, float y, float z, float w) : _x(x), _y(y), _z(z), _w(w) {}
};


struct alignas(16) std140Mat4 {
    std140Vec4 col1, col2, col3, col4;

    std140Mat4(Matrix4f mat) : col1({mat.at(0, 0), mat.at(1, 0), mat.at(2, 0), mat.at(3, 0)}),
                               col2({mat.at(0, 1), mat.at(1, 1), mat.at(2, 1), mat.at(3, 1)}),
                               col3({mat.at(0, 2), mat.at(1, 2), mat.at(2, 2), mat.at(3, 2)}),
                               col4({mat.at(0, 3), mat.at(1, 3), mat.at(2, 3), mat.at(3, 3)}) {}
};


struct alignas(16) std140BPMonoChromaticMaterial {
    std140Vec3 specular;
    std140Vec3 color;
    std140float ambient;
    std140float diffuse;
    std140float shininess;

    std140BPMonoChromaticMaterial() {}

    std140BPMonoChromaticMaterial(BPMonochromaticMaterial *mat) :
            ambient(mat->ambient),
            diffuse(mat->diffuse),
            specular({mat->specular}),
            color({mat->color}),
            shininess(mat->shininess) {}
};

struct std140BPMonoChromaticMaterialArray {

};



#endif //TRUCKER_GAME_STD140_H

#ifndef TRUCKER_GAME_VECTOR3F_H
#define TRUCKER_GAME_VECTOR3F_H


class Vector3f {
private:
    float _x, _y, _z;
public:
    Vector3f() : _x(0.0f), _y(0.0f), _z(0.0f) {}

    Vector3f(float x, float y, float z) : _x(x), _y(y), _z(z) {}

    [[nodiscard]] float getX() const;

    [[nodiscard]] float getY() const;

    [[nodiscard]] float getZ() const;
};


#endif //TRUCKER_GAME_VECTOR3F_H

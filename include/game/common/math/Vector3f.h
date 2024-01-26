#ifndef TRUCKER_GAME_VECTOR3F_H
#define TRUCKER_GAME_VECTOR3F_H


class Vector3f {
private:
    float _x, _y;
public:
    Vector3f(float x, float y) : _x(x), _y(y) {}

    [[nodiscard]] float getX() const;

    [[nodiscard]] float getY() const;
};


#endif //TRUCKER_GAME_VECTOR3F_H

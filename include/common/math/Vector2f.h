#ifndef TRUCKER_GAME_VECTOR2F_H
#define TRUCKER_GAME_VECTOR2F_H


class Vector2f {
private:
    float _x, _y;
public:
    Vector2f(float x, float y) : _x(x), _y(y) {}

    [[nodiscard]] float getX() const;

    [[nodiscard]] float getY() const;
};


#endif //TRUCKER_GAME_VECTOR2F_H

#ifndef TRUCKER_GAME_POSITIONCOMPONENT_H
#define TRUCKER_GAME_POSITIONCOMPONENT_H

#include "game/common/math/Vector3f.h"

struct PositionComponent {
public:
    Vector3f pos = {0.0f, 0.0f};
    explicit PositionComponent(Vector3f pPos) : pos(pPos) {}
    PositionComponent() = default;
};

#endif //TRUCKER_GAME_POSITIONCOMPONENT_H

#ifndef TRUCKER_GAME_TRANSFORMCOMPONENT_H
#define TRUCKER_GAME_TRANSFORMCOMPONENT_H

#include <memory>
#include "common/math/Vector3f.h"
#include "common/math/Quaternion.h"

struct TransformComponent
{
public:
    shared_ptr<Vector3f> position;
    shared_ptr<Quaternion> orientation;
    shared_ptr<Vector3f> scale;
    bool is_dirty = false;

    TransformComponent(const Vector3f &position, const Quaternion &orientation, const Vector3f &scale)
        : position(std::make_shared<Vector3f>(position)),
          orientation(std::make_shared<Quaternion>(orientation)),
          scale(std::make_shared<Vector3f>(scale)){
    }

    TransformComponent() = default;
};

#endif // TRUCKER_GAME_TRANSFORMCOMPONENT_H

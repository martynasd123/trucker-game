#ifndef TRUCKER_GAME_CAMERA_H
#define TRUCKER_GAME_CAMERA_H

#include "common/math/Matrix4f.h"

class Camera {
private:
    Matrix4f mProjection = Matrix4f::IDENTITY;
    Matrix4f mView = Matrix4f::IDENTITY;
public:
    [[nodiscard]] const Matrix4f &getProjection() const;

    void setProjection(const Matrix4f projection);

    [[nodiscard]] const Matrix4f &getView() const;

    void setView(const Matrix4f &view);
};


#endif //TRUCKER_GAME_CAMERA_H

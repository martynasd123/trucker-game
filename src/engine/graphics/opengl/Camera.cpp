#include "engine/graphics/opengl/Camera.h"

const Matrix4f &Camera::getProjection() const {
    return this->mProjection;
}

void Camera::setProjection(const Matrix4f projection) {
    this->mProjection = projection;
}

const Matrix4f &Camera::getView() const {
    return mView;
}

void Camera::setView(const Matrix4f &view) {
    mView = view;
}

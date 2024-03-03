#ifndef TRUCKER_GAME_VERTEXARRAYOBJECT_H
#define TRUCKER_GAME_VERTEXARRAYOBJECT_H

#include "glad/glad.h"
#include "common/math/Vector3f.h"
#include "common/math/Vector2f.h"

class VertexArrayObject {
private:
    GLuint id;
public:
    VertexArrayObject();

    void bind() const;

    void unbind() const;
};

#endif //TRUCKER_GAME_VERTEXARRAYOBJECT_H

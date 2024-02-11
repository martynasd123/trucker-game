#ifndef TRUCKER_GAME_VERTEXARRAYOBJECT_H
#define TRUCKER_GAME_VERTEXARRAYOBJECT_H

#include "engine/graphics/opengl/buffer/VertexBufferObject.h"
#include "common/math/Vector3f.h"
#include "common/math/Vector2f.h"

class VertexArrayObject {
private:
    GLuint id;
public:
    VertexArrayObject();

    template<typename T>
    void addVertexAttribute(unsigned int index, VertexBufferObject<T>* vbo);

    void addElementBuffer(VertexBufferObject<int>* vbo);

    void bind();

    void unbind();
};

template<> void VertexArrayObject::addVertexAttribute<Vector3f>(unsigned int index, VertexBufferObject<Vector3f>* vbo);
template<> void VertexArrayObject::addVertexAttribute<Vector2f>(unsigned int index, VertexBufferObject<Vector2f>* vbo);

#endif //TRUCKER_GAME_VERTEXARRAYOBJECT_H

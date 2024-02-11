#ifndef TRUCKER_GAME_VERTEXBUFFEROBJECT_H
#define TRUCKER_GAME_VERTEXBUFFEROBJECT_H

#include <glad/glad.h>
#include <vector>
#include "common/math/Vector3f.h"
#include "common/math/Vector2f.h"

using namespace std;

template<typename T>
class VertexBufferObject {
protected:
    GLuint mId{};
    GLenum mType;
public:
    explicit VertexBufferObject(int size, GLenum type): mType(type) {
        glGenBuffers(1, &mId);
        bind();
        allocateBuffer(size);
        unbind();
    }

    explicit VertexBufferObject(int size): VertexBufferObject(size, GL_ARRAY_BUFFER) { }

    void bind() {
        glBindBuffer(mType, mId);
    }

    void unbind() {
        glBindBuffer(mType, 0);
    }

    void setData(vector<T>::iterator begin, vector<T>::iterator end, unsigned int offset);

    void allocateBuffer(int size);

    GLenum getType() {
        return mType;
    }
};

#endif //TRUCKER_GAME_VERTEXBUFFEROBJECT_H

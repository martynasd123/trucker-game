#ifndef TRUCKER_GAME_VERTEXBUFFEROBJECT_H
#define TRUCKER_GAME_VERTEXBUFFEROBJECT_H

#include "glad/glad.h"
#include <vector>

using namespace std;

template<typename T>
class VertexBufferObject {
protected:
    GLuint id{};
    virtual void allocateBuffer(int size) = 0;
public:

    void bind() {
        glBindBuffer(GL_ARRAY_BUFFER, id);
    }

    void unbind() {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    VertexBufferObject(int size) {
        glGenBuffers(1, &id);
        bind();
        allocateBuffer(size);
        unbind();
    }

    virtual void setData(vector<T>::iterator begin, vector<T>::iterator end, unsigned int offset) = 0;
};


#endif //TRUCKER_GAME_VERTEXBUFFEROBJECT_H

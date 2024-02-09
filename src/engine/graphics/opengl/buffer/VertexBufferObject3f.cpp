#include "engine/graphics/opengl/buffer/VertexBufferObject3f.h"

void VertexBufferObject3f::allocateBuffer(int size) {
    glBufferData(GL_ARRAY_BUFFER, size * sizeof(float) * 3, nullptr, GL_DYNAMIC_DRAW);
}

void
VertexBufferObject3f::setData(vector<Vector3f>::iterator begin, vector<Vector3f>::iterator end, unsigned int offset) {
    int numElements = distance(begin, end);
    const int elementSizeInBytes = sizeof(float) * 3;
    Vector3f vectors[numElements];
    int i = 0;
    for (auto it = begin; it < end; it++) {
        vectors[i++] = *it;
    }
    glBindBuffer(GL_ARRAY_BUFFER, id);
    glBufferSubData(GL_ARRAY_BUFFER, offset * elementSizeInBytes, numElements * elementSizeInBytes, &vectors);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
#include "engine/graphics/opengl/buffer/VertexBufferObject2f.h"

void VertexBufferObject2f::allocateBuffer(int size) {
    glBufferData(GL_ARRAY_BUFFER, size * sizeof(float) * 2, nullptr, GL_DYNAMIC_DRAW);
}

void
VertexBufferObject2f::setData(vector<Vector2f>::iterator begin, vector<Vector2f>::iterator end, unsigned int offset) {
    int numElements = distance(begin, end);
    const int elementSizeInBytes = sizeof(float) * 2;
    Vector2f vectors[numElements];
    int i = 0;
    for (auto it = begin; it < end; it++) {
        vectors[i++] = *it;
    }
    glBindBuffer(GL_ARRAY_BUFFER, id);
    glBufferSubData(GL_ARRAY_BUFFER, offset * elementSizeInBytes, numElements * elementSizeInBytes, &vectors);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
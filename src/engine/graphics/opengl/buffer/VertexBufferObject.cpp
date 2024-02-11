#include "engine/graphics/opengl/buffer/VertexBufferObject.h"

template<>
void VertexBufferObject<Vector3f>::setData(vector<Vector3f>::iterator begin, vector<Vector3f>::iterator end, unsigned int offset) {
    float vectors[distance(begin, end) * 3];
    int i = 0;
    for (auto it = begin; it < end; it++) {
        vectors[i++] = it->getX();
        vectors[i++] = it->getY();
        vectors[i++] = it->getZ();
    }
    bind();
    glBufferSubData(mType, offset * sizeof(float) * 3, i * sizeof(float), &vectors);
    unbind();
}

template<> void VertexBufferObject<Vector3f>::allocateBuffer(int size) {
    glBufferData(mType, size * sizeof(float) * 3, nullptr, GL_DYNAMIC_DRAW);
}

template<>
void VertexBufferObject<Vector2f>::setData(vector<Vector2f>::iterator begin, vector<Vector2f>::iterator end, unsigned int offset) {
    float vectors[distance(begin, end) * 2];
    int i = 0;
    for (auto it = begin; it < end; it++) {
        vectors[i++] = it->getX();
        vectors[i++] = it->getY();
    }
    bind();
    glBufferSubData(mType, offset * sizeof(float) * 2, i * sizeof(float), &vectors);
    unbind();
}

template<> void VertexBufferObject<Vector2f>::allocateBuffer(int size) {
    glBufferData(mType, size * sizeof(float) * 2, nullptr, GL_DYNAMIC_DRAW);
}

template<>
void VertexBufferObject<int>::setData(vector<int>::iterator begin, vector<int>::iterator end, unsigned int offset) {
    int elements[distance(begin, end)];
    int i = 0;
    for (auto it = begin; it < end; it++) {
        elements[i++] = *it;
    }
    bind();
    glBufferSubData(mType, offset * sizeof(int), i * sizeof(int), &elements);
    unbind();
}

template<> void VertexBufferObject<int>::allocateBuffer(int size) {
    glBufferData(mType, size * sizeof(int), nullptr, GL_DYNAMIC_DRAW);
}


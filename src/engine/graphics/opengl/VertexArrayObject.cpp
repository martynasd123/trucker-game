#include "engine/graphics/opengl/VertexArrayObject.h"

VertexArrayObject::VertexArrayObject() {
    glGenVertexArrays(1, &id);
}

void VertexArrayObject::bind() {
    glBindVertexArray(id);
}

void VertexArrayObject::unbind() {
    glBindVertexArray(0);
}

void VertexArrayObject::addElementBuffer(VertexBufferObject<int>* vbo) {
    if (vbo->getType() != GL_ELEMENT_ARRAY_BUFFER) {
        throw invalid_argument("Unexpected buffer type passed to addElementBuffer");
    }
    bind();
    vbo->bind();
    unbind();
    vbo->unbind();
}

template<> void VertexArrayObject::addVertexAttribute<Vector3f>(unsigned int index, VertexBufferObject<Vector3f> *vbo) {
    bind();
    vbo->bind();
    glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(index);
    unbind();
    vbo->unbind();
}

template<> void VertexArrayObject::addVertexAttribute<Vector2f>(unsigned int index, VertexBufferObject<Vector2f> *vbo) {
    bind();
    vbo->bind();
    glVertexAttribPointer(index, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(index);
    unbind();
    vbo->unbind();
}
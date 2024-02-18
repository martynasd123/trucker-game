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

void VertexArrayObject::addElementBuffer(ElementBufferObject* ebo) {
    bind();
    ebo->bind();
    unbind();
    ebo->unbind();
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

template<> void VertexArrayObject::addVertexAttribute<unsigned int>(unsigned int index, VertexBufferObject<unsigned int> *vbo) {
    bind();
    vbo->bind();
    glVertexAttribPointer(index, 1, GL_UNSIGNED_INT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(index);
    unbind();
    vbo->unbind();
}
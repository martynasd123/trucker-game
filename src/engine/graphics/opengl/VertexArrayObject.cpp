#include "engine/graphics/opengl/VertexArrayObject.h"

VertexArrayObject::VertexArrayObject() {
    glGenVertexArrays(1, &id);
}

void VertexArrayObject::bind() const {
    glBindVertexArray(id);
}

void VertexArrayObject::unbind() const {
    glBindVertexArray(0);
}

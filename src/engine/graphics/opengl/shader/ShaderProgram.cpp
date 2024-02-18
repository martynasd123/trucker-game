#include "engine/graphics/opengl/shader/ShaderProgram.h"
#include "common/math/Matrix4f.h"
#include <iostream>

ShaderProgram::~ShaderProgram() {
    if (mId.has_value()) {
        glDeleteProgram(*mId);
    }
}

void ShaderProgram::link() {
    glLinkProgram(*mId);
    GLint result;
    glGetProgramiv(*mId, GL_LINK_STATUS, &result);
    if (result != GL_TRUE) {
        int errorMessageLength;
        glGetProgramiv(*mId, GL_INFO_LOG_LENGTH, &errorMessageLength);
        char* msg = new char[errorMessageLength];
        glGetProgramInfoLog(*mId, errorMessageLength, nullptr, msg);
        string error = string("Failed to link shader program: ") + msg;
        delete[] msg;
        throw runtime_error(error);
    }
}

void ShaderProgram::use() const {
    glUseProgram(*mId);
}

void ShaderProgram::bindUBO(const std::string& name, GLuint bindingPoint) const {
    unsigned int index = glGetUniformBlockIndex(*mId, name.c_str());
    glUniformBlockBinding(*mId, index, bindingPoint);
}

ShaderProgram::ShaderProgram() : mId(glCreateProgram()) {
}

ShaderProgram::ShaderProgram(ShaderProgram &&other) {
    this->mId = other.mId;
    other.mId = optional<GLuint>();
}

ShaderProgram::ShaderProgram(ShaderProgram const &other) noexcept {
    this->mId = other.mId;
}

template<>
void ShaderProgram::setUniform(std::string name, const Matrix4f value) const {
    GLint uniformLocation = glGetUniformLocation(*mId, name.c_str());
    glProgramUniformMatrix4fv(*mId, uniformLocation, 1, GL_TRUE, value.array());
}

template<>
void ShaderProgram::setUniform(std::string name, const int value) const {
    GLint uniformLocation = glGetUniformLocation(*mId, name.c_str());
    glProgramUniform1i(*mId, uniformLocation, value);
}
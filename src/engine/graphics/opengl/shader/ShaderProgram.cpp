#include "engine/graphics/opengl/shader/ShaderProgram.h"

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(mId);
}

void ShaderProgram::link() {
    glLinkProgram(mId);
    GLint result;
    glGetProgramiv(mId, GL_LINK_STATUS, &result);
    if (result != GL_TRUE) {
        int errorMessageLength;
        glGetProgramiv(mId, GL_INFO_LOG_LENGTH, &errorMessageLength);
        char* msg = new char[errorMessageLength];
        glGetProgramInfoLog(mId, errorMessageLength, nullptr, msg);
        string error = string("Failed to link shader program: ") + msg;
        delete[] msg;
        throw runtime_error(error);
    }
}

void ShaderProgram::use() {
    glUseProgram(mId);
}
#include "engine/graphics/opengl/util/GLUtils.h"
#include <stdexcept>
#include <string>
#include <glad/glad.h>

using namespace std;

string getErrorTypeString(GLenum error) {
    if (error == GL_INVALID_ENUM) {
        return "GL_INVALID_ENUM";
    } else if (error == GL_INVALID_VALUE) {
        return "GL_INVALID_VALUE";
    } else if (error == GL_INVALID_OPERATION) {
        return "GL_INVALID_OPERATION";
    } else if (error == GL_INVALID_FRAMEBUFFER_OPERATION) {
        return "GL_INVALID_FRAMEBUFFER_OPERATION";
    } else if (error == GL_OUT_OF_MEMORY) {
        return "GL_OUT_OF_MEMORY";
    } else if (error == GL_STACK_UNDERFLOW) {
        return "GL_STACK_UNDERFLOW";
    } else if (error == GL_STACK_OVERFLOW) {
        return "GL_STACK_OVERFLOW";
    } else {
        throw invalid_argument("Uknown error type " + to_string(error));
    }
}

namespace GL_UTIL {
    void checkError() {
        GLenum error = glGetError();
        if (error != GL_NO_ERROR) {
            throw runtime_error("OpenGL error encountered " + getErrorTypeString(error));
        }
    }
}
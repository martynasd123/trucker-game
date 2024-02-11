#include "engine/graphics/opengl/shader/FragmentShader.h"

FragmentShader::FragmentShader(const string& code) {
    mId = glCreateShader(GL_FRAGMENT_SHADER);
    mType = GL_FRAGMENT_SHADER;
    compileShader(code);
}

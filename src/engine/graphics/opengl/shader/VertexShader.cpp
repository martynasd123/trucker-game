#include "engine/graphics/opengl/shader/VertexShader.h"

VertexShader::VertexShader(const string& code): Shader() {
    mId = glCreateShader(GL_VERTEX_SHADER);
    mType = GL_VERTEX_SHADER;
    compileShader(code);
}

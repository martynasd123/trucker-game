#include "engine/graphics/opengl/shader/Shader.h"

#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

void Shader::checkCompileError() const {
    int isSuccess;
    glGetShaderiv(mId, GL_COMPILE_STATUS, &isSuccess);
    if (isSuccess != GL_TRUE) {
        int buffLength;
        glGetShaderiv(mId, GL_INFO_LOG_LENGTH, &buffLength);
        char* buff = new char[buffLength];
        glGetShaderInfoLog(mId, buffLength, nullptr, buff);
        string msg = string("Error while compiling shader: ") + buff;
        delete[] buff;
        throw runtime_error(msg);
    }
}

void Shader::compileShader(const std::string& source) const {
    istringstream inputStream(source);
    vector<string> lines;
    string line;
    while (getline(inputStream, line)) {
        lines.push_back(line + "\n");
    }

    const char** ptrs = new const char*[lines.size()];
    for (int i = 0; i < lines.size(); ++i) {
        ptrs[i] = lines[i].c_str();
    }
    glShaderSource(mId, lines.size(), ptrs, nullptr);

    delete[] ptrs;

    glCompileShader(mId);
    checkCompileError();
}

GLuint Shader::getId() {
    return mId;
}

Shader::~Shader() {
    glDeleteShader(mId);
}

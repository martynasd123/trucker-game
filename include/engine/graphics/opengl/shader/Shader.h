#ifndef TRUCKER_GAME_SHADER_H
#define TRUCKER_GAME_SHADER_H

#include <glad/glad.h>
#include <string>

using namespace std;

class Shader {
private:
    void checkCompileError() const;
protected:
    GLuint mId{};
    GLenum mType{};
    void compileShader(const string& source) const;
public:
    GLuint getId();
    virtual ~Shader();
};


#endif //TRUCKER_GAME_SHADER_H

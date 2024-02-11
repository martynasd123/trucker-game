#ifndef TRUCKER_GAME_SHADERPROGRAM_H
#define TRUCKER_GAME_SHADERPROGRAM_H

#include "Shader.h"

class ShaderProgram {
private:
    GLuint mId = glCreateProgram();
public:
    template <typename ShaderType, typename = std::enable_if_t<std::is_base_of<Shader, ShaderType>::value>>
    void addShader(ShaderType* shaderDerived) {
        auto shader = dynamic_cast<Shader*>(shaderDerived);
        glAttachShader(mId, shader->getId());
    }

    void link();

    void use();

    virtual ~ShaderProgram();
};


#endif //TRUCKER_GAME_SHADERPROGRAM_H

#ifndef TRUCKER_GAME_SHADERPROGRAM_H
#define TRUCKER_GAME_SHADERPROGRAM_H

#include "Shader.h"

class ShaderProgram {
private:
    optional<GLuint> mId;
public:

    explicit ShaderProgram();

    ShaderProgram(ShaderProgram&& other);

    ShaderProgram(ShaderProgram const &other) noexcept;

        template <typename ShaderType, typename = std::enable_if_t<std::is_base_of<Shader, ShaderType>::value>>
    void addShader(ShaderType* shaderDerived) {
        auto shader = dynamic_cast<Shader*>(shaderDerived);
        glAttachShader(*mId, shader->getId());
    }

    void link();

    void use() const;

    /**
     * Sets the uniform of a given type to this shader program.
     * @tparam T Type of uniform to set
     * @param name Name of uniform
     * @param value Value of uniform
     */
    template<typename T>
    void setUniform(const string& name, const T& value) const;

    void bindUBO(const string& name, GLuint bindingPoint) const;

    virtual ~ShaderProgram();
};


#endif //TRUCKER_GAME_SHADERPROGRAM_H

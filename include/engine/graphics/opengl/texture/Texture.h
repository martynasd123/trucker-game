#ifndef TRUCKER_GAME_TEXTURE_H
#define TRUCKER_GAME_TEXTURE_H

#include <glad/glad.h>
#include <memory>

class Texture {
protected:
    GLuint mTarget{};
    std::shared_ptr<GLuint> mId;
    Texture();
public:
    void bind() const;
    void unbind() const;
    void setParameter(GLenum name, GLint value);
    [[nodiscard]] GLuint getId() const;
    virtual ~Texture() = default;
};


#endif //TRUCKER_GAME_TEXTURE_H

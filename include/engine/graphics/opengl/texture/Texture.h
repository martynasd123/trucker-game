#ifndef TRUCKER_GAME_TEXTURE_H
#define TRUCKER_GAME_TEXTURE_H

#include <glad/glad.h>

class Texture {
protected:
    GLuint mTarget{};
    GLuint mId{};
    Texture();
public:
    void bind();
    void unbind();
    void setParameter(GLenum name, GLint value);
    [[nodiscard]] GLuint getId() const;
};


#endif //TRUCKER_GAME_TEXTURE_H

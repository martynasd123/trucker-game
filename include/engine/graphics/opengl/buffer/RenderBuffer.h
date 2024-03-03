#ifndef TRUCKER_GAME_RENDERBUFFER_H
#define TRUCKER_GAME_RENDERBUFFER_H

#include <memory>
#include "glad/glad.h"

class RenderBuffer {
protected:
    std::shared_ptr<GLuint> mId;
public:
    explicit RenderBuffer(GLenum internalFormat, unsigned int width, unsigned int height);

    void bind();

    void unbind();

    GLuint getId();
};


#endif //TRUCKER_GAME_RENDERBUFFER_H

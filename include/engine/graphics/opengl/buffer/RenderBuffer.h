#ifndef TRUCKER_GAME_RENDERBUFFER_H
#define TRUCKER_GAME_RENDERBUFFER_H


#include "glad/glad.h"

class RenderBuffer {
protected:
    GLuint mId;
public:
    explicit RenderBuffer(GLenum internalFormat, unsigned int width, unsigned int height);

    RenderBuffer(RenderBuffer&& other) noexcept;

    RenderBuffer(const RenderBuffer&) = delete;

    void bind();

    void unbind();

    GLuint getId();

    virtual ~RenderBuffer();
};


#endif //TRUCKER_GAME_RENDERBUFFER_H

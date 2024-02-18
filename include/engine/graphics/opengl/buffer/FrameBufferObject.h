#ifndef TRUCKER_GAME_FRAMEBUFFEROBJECT_H
#define TRUCKER_GAME_FRAMEBUFFEROBJECT_H

#include "glad/glad.h"

class FrameBufferObject {
protected:
    GLuint mId;
public:
    explicit FrameBufferObject();

    FrameBufferObject(FrameBufferObject&& other) noexcept;

    FrameBufferObject(const FrameBufferObject& other) = delete;

    void bind();

    void unbind();

    virtual ~FrameBufferObject() {
        if (mId != -1) {
            glDeleteFramebuffers(1, &mId);
        }
    }
};


#endif //TRUCKER_GAME_FRAMEBUFFEROBJECT_H

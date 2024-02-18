#ifndef TRUCKER_GAME_TEXTURE2D_H
#define TRUCKER_GAME_TEXTURE2D_H

#include "Texture.h"

class Texture2D: public Texture {
private:
    void setParameters();
public:
    Texture2D(GLint level,
              GLint internalformat,
              GLsizei width,
              GLsizei height,
              GLenum format,
              GLenum type);
};


#endif //TRUCKER_GAME_TEXTURE2D_H

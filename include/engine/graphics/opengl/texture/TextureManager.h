#ifndef TRUCKER_GAME_TEXTUREMANAGER_H
#define TRUCKER_GAME_TEXTUREMANAGER_H

#include "Texture.h"
#include "glad/glad.h"
#include "../shader/ShaderProgram.h"
#include "vector"
#include "optional"

using namespace std;

class TextureManager {
protected:
    vector<Texture*> mTextureSlots;
    vector<bool> mReservedTextureSlots;
    GLint mMaxTextureSlots;
public:
    TextureManager();

    void begin();

    void addTexture(Texture& texture);

    GLuint getTextureSlot(Texture& texture);

    void bindTexture(Texture& texture, const ShaderProgram& program, string uniform);

    void end();
};


#endif //TRUCKER_GAME_TEXTUREMANAGER_H

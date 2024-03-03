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
    vector<const Texture*> mTextureSlots;
    vector<bool> mReservedTextureSlots;
    GLint mMaxTextureSlots;
public:
    TextureManager();

    void begin();

    void addTexture(const Texture& texture);

    GLuint getTextureSlot(Texture& texture) const;

    void bindTexture(const Texture& texture, const ShaderProgram& program, string uniform);

    void forgetTexture(const Texture& texture);

    void end();
};


#endif //TRUCKER_GAME_TEXTUREMANAGER_H

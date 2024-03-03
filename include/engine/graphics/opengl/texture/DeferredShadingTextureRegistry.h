#ifndef TRUCKER_GAME_DEFERREDSHADINGTEXTUREREGISTRY_H
#define TRUCKER_GAME_DEFERREDSHADINGTEXTUREREGISTRY_H


#include "Texture2D.h"

class DeferredShadingTextureRegistry {
private:
    GLsizei width, height;
    Texture2D mAlbedoTexture, mPositionTexture, mNormalTexture, mMaterialDataTexture;

    [[nodiscard]] Texture2D initAlbedoTexture() const;
    [[nodiscard]] Texture2D initPositionTexture() const;
    [[nodiscard]] Texture2D initNormalTexture() const;
    [[nodiscard]] Texture2D initMaterialDataTexture() const;
public:
    DeferredShadingTextureRegistry(GLsizei width, GLsizei height);

    /**
     * Re-creates all textures with the new given size.
     * @param pWidth The new pWidth
     * @param pHeight The new pHeight
     */
    void updateDimensions(const GLsizei& pWidth, const GLsizei& pHeight);

    [[nodiscard]] const Texture2D &getAlbedoTexture() const;

    [[nodiscard]] const Texture2D &getPositionTexture() const;

    [[nodiscard]] const Texture2D &getNormalTexture() const;

    [[nodiscard]] const Texture2D &getMaterialDataTexture() const;
};


#endif //TRUCKER_GAME_DEFERREDSHADINGTEXTUREREGISTRY_H

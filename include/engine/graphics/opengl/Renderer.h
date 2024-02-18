#ifndef TRUCKER_GAME_RENDERER_H
#define TRUCKER_GAME_RENDERER_H

#include "common/render/Mesh.h"
#include "common/render/Light.h"
#include "common/math/Transform.h"
#include "engine/graphics/opengl/ObjectBasedBatch.h"
#include "engine/graphics/opengl/pass/GeometryPass.h"
#include "engine/graphics/opengl/pass/LightingPass.h"
#include "engine/graphics/opengl/Definitions.h"
#include "engine/graphics/opengl/material/MaterialHandlerRegistry.h"
#include "engine/graphics/opengl/texture/TextureManager.h"

#include <queue>
#include <type_traits>

using namespace std;

class Renderer {
private:
    ObjectBasedBatch* mBatches[MAX_OBJECTS]{};
    Light* mLights[MAX_LIGHTS]{};
    queue<MeshId> mAvailableMeshIds;
    queue<LightId> mAvailableLightIds;

    MaterialHandlerRegistry& mHandlerRegistry;
    UniformBufferObject mLightsUbo;
    TextureManager mTextureManager;

    // Textures
    Texture2D mAlbedoTexture;
    Texture2D mPositionTexture;
    Texture2D mNormalTexture;

    // Passes
    GeometryPass mGeometryPass;
    LightingPass mLightingPass;
public:
    explicit Renderer();
    MeshId addMesh(Mesh* mesh, Transform transform);

    template<class T>
    LightId addLight(T light);

    void removeMesh(MeshId id);
    void updateTransform(MeshId id, Transform transform);
    void draw();
};

template<class T>
LightId Renderer::addLight(T light) {
    static_assert(std::is_base_of<Light, T>::value, "Light must be derived from the Light base class");
    LightId lightId = mAvailableLightIds.front();
    mAvailableLightIds.pop();
    mLights[lightId] = new T(std::move(light));
    return lightId;
}

#endif //TRUCKER_GAME_RENDERER_H

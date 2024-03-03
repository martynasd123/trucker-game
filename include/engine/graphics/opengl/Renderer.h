#ifndef TRUCKER_GAME_RENDERER_H
#define TRUCKER_GAME_RENDERER_H

#include "common/render/Mesh.h"
#include "common/render/Light.h"
#include "common/math/Vector4f.h"
#include "common/math/Transform.h"
#include "engine/graphics/opengl/ObjectBasedBatch.h"
#include "engine/graphics/opengl/util/MappedVector.h"
#include "engine/graphics/opengl/pass/GeometryPass.h"
#include "engine/graphics/opengl/pass/LightingPass.h"
#include "engine/graphics/opengl/Definitions.h"
#include "engine/graphics/opengl/material/MaterialHandlerRegistry.h"
#include "engine/graphics/opengl/texture/TextureManager.h"
#include "engine/graphics/opengl/texture/DeferredShadingTextureRegistry.h"

#include <queue>
#include <type_traits>

using namespace std;

class Renderer {
private:
    MappedVector<shared_ptr<ObjectBasedBatch>> mBatches;
    MappedVector<shared_ptr<Light>> mLights;

    Camera mCam;

    MaterialHandlerRegistry mHandlerRegistry;
    GLBufferArrayList<PointLight> mPointLightsUbo;
    TextureManager mTextureManager;

    DeferredShadingTextureRegistry mDeferredShadingTextureRegistry;

    // Passes
    GeometryPass mGeometryPass;
    LightingPass mLightingPass;
public:
    explicit Renderer();

    MeshId addMesh(const Mesh& mesh, Transform transform);

    template<class T>
    LightId addLight(T light);

    LightId removeLight(LightId id);

    void removeMesh(MeshId id);

    void updateTransform(MeshId id, Transform transform);

    void draw();
};

#endif //TRUCKER_GAME_RENDERER_H

#ifndef TRUCKER_GAME_MESHRESOURCERESOLVER_H
#define TRUCKER_GAME_MESHRESOURCERESOLVER_H


#include "engine/resource/MeshResource.h"
#include "engine/resource/resolver/ResourceResolver.h"

class MeshResourceResolver: public ResourceResolver<MeshResource> {
public:
    MeshResource resolveResource(ResourcePath resPath) override;

    void destroyResource(MeshResource resource) override;
};


#endif //TRUCKER_GAME_MESHRESOURCERESOLVER_H

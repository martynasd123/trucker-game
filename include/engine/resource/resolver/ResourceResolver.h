#ifndef TRUCKER_GAME_RESOURCERESOLVER_H
#define TRUCKER_GAME_RESOURCERESOLVER_H


#include "engine/resource/Resource.h"
#include "engine/resource/Types.h"

class ResourceResolverBase {
};

template<class T>
class ResourceResolver: public ResourceResolverBase {
public:
    virtual T resolveResource(ResourcePath resPath) = 0;
    virtual void destroyResource(T resource) = 0;
};

#endif //TRUCKER_GAME_RESOURCERESOLVER_H

#ifndef TRUCKER_GAME_TEXTRESOURCERESOLVER_H
#define TRUCKER_GAME_TEXTRESOURCERESOLVER_H


#include "engine/resource/TextResource.h"
#include "ResourceResolver.h"

class TextResourceResolver: public ResourceResolver<TextResource> {
    TextResource resolveResource(ResourcePath resPath) override;
    void destroyResource(TextResource resource) override;
};


#endif //TRUCKER_GAME_TEXTRESOURCERESOLVER_H

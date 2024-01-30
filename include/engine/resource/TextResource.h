#ifndef TRUCKER_GAME_TEXTRESOURCE_H
#define TRUCKER_GAME_TEXTRESOURCE_H

#include <string>
#include <utility>
#include "Resource.h"

class TextResource: public Resource {
public:
    std::string text;
    explicit TextResource(std::string pText) : text(std::move(pText)) {};
    ~TextResource() override = default;
};

#endif //TRUCKER_GAME_TEXTRESOURCE_H

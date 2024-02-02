#include "engine/resource/resolver/TextResourceResolver.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>


TextResource TextResourceResolver::resolveResource(ResourcePath resPath) {
    std::ifstream inputFile(resPath);

    if (!inputFile.is_open()) {
        throw std::invalid_argument("Unable to open text resource file " + resPath);
    }

    std::string acc;
    std::string line;
    bool addNewline = false;
    while (std::getline(inputFile, line)) {
        if (addNewline) {
            acc += "\n" + line;
        } else {
            acc += line;
        }
        addNewline = true;
    }

    inputFile.close();
    return TextResource (acc);
}

void TextResourceResolver::destroyResource(TextResource resource) {
    resource.~TextResource();
}

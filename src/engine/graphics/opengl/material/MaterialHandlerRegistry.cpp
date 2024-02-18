#include "engine/graphics/opengl/material/MaterialHandlerRegistry.h"

const MaterialHandler &MaterialHandlerRegistry::getHandler(const string& materialType) {
    if (!mMaterialHandlers.contains(materialType)) {
        throw runtime_error("No material handler registered for " + materialType);
    }
    return mMaterialHandlers.at(materialType);
}

const vector<const MaterialHandler*> MaterialHandlerRegistry::getHandlers() {
    vector<const MaterialHandler*> handlers;
    handlers.reserve(mMaterialHandlers.size());
    for (const auto &entry: mMaterialHandlers) {
        handlers.push_back(&entry.second);
    }
    return std::move(handlers);
}
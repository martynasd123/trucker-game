#include "engine/resource/manager/ResourceManager.h"

#include <utility>

bool ResourceSignature::operator==(const ResourceSignature &rhs) const {
    return path == rhs.path &&
           resolverId == rhs.resolverId;
}

bool ResourceSignature::operator!=(const ResourceSignature &rhs) const {
    return !(rhs == *this);
}

ResourceSignature::ResourceSignature(ResourcePath path, ResourceResolverId resolverId) : path(std::move(path)),
                                                                                         resolverId(
                                                                                                 resolverId) {}

ResourceManager::ResourceManager() {
    for (int i = 0; i < MAX_RESOURCES; ++i) {
        mAvailableHandles.push(i);
    }
}

void ResourceManager::releaseResource(ResourceHandle resourceHandle) {
    if (resourceHandle >= MAX_RESOURCES || mRefCount[resourceHandle] == 0) {
        throw std::invalid_argument("Invalid resource handle");
    }
    mRefCount[resourceHandle]--;
    if (mRefCount[resourceHandle] == 0) {
        delete mResources[resourceHandle];
        mAvailableHandles.push(resourceHandle);
        for (const auto &item: mHandleMap) {
            if (item.second == resourceHandle) {
                mHandleMap.erase(item.first);
                return;
            }
        }
    }
}

ResourceResolverId ResolverIDMapper::nextId = 0;

ResourceManager::~ResourceManager() {
    for (const auto &resource: mResources) {
        delete resource;
    }
    for (const auto &resolver: mResourceResolvers) {
        delete resolver;
    }
}

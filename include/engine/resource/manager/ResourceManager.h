#ifndef TRUCKER_GAME_RESOURCEMANAGER_H
#define TRUCKER_GAME_RESOURCEMANAGER_H

#include <queue>
#include <string>
#include "engine/resource/Types.h"
#include "engine/resource/resolver/ResourceResolver.h"

struct ResourceSignature {
    ResourcePath path;
    ResourceResolverId resolverId;

    ResourceSignature(ResourcePath path, ResourceResolverId resolverId);

    bool operator==(const ResourceSignature &rhs) const;

    bool operator!=(const ResourceSignature &rhs) const;
};


namespace std {
    template <>
    struct hash<ResourceSignature> {
        std::size_t operator()(const ResourceSignature &signature) const {
            // Combine the hashes of path and resolverId
            std::size_t hashValue = std::hash<std::string>{}(signature.path);
            hashValue ^= std::hash<unsigned int>{}(signature.resolverId);
            return hashValue;
        }
    };
}



class ResolverIDMapper {
private:
    static ResourceResolverId nextId;
public:
    template<typename T>
    ResourceResolverId getId() {
        static const ResourceResolverId id = nextId++;
        return id;
    }
};

class ResourceManager {
private:
    ResourceResolverBase* mResourceResolvers[MAX_RESOURCE_RESOLVERS]{};
    Resource* mResources[MAX_RESOURCES]{};
    unsigned int mRefCount[MAX_RESOURCES]{};
    std::unordered_map<ResourceSignature, ResourceHandle> mHandleMap;
    std::queue<ResourceHandle> mAvailableHandles;
public:
    ResourceManager();

    virtual ~ResourceManager();

    /**
     * Register a resource resolver of a given type with given arguments
     * @tparam T Type of resource the resolver will handle. Must be a derivative of ResourceResolver
     * @tparam ResolverType The type of resource resolver
     * @tparam ResourceType The type of resource to be resolved
     * @tparam Args Argument types to the constructor of resource resolver
     * @param args Arguments to the constructor of resource resolver
     */
    template<typename ResolverType, typename ResourceType, typename... Args>
    void registerResourceResolver(Args&&... args);

    /**
     * Acquires a handle to a specified resource. Loads the resource if needed.
     * @tparam T Type of resource to acquire a handle for
     * @param path Path to desired resource
     * @return A valid resource handle
     */
    template<typename T>
    ResourceHandle acquireHandle(std::string path);

    /**
     * Get a resource for a given handle
     * @tparam T Type of resource to retrieve
     * @param resourceHandle A valid resource handle
     * @return Pointer to the requested resource. Guaranteed to be valid until releaseResource is called
     */
    template<typename T>
    T* getResource(ResourceHandle resourceHandle);

    /**
     * Move resource with a given handle. If it is safe to do so, the resource will be moved. Otherwise, a copy
     * of the resource will be made and it will be moved.
     * @tparam T Type of resource to move
     * @param handle A valid resource handle
     * @return Resource r-value
     */
    template<typename T>
    T&& moveResource(ResourceHandle handle);

    /**
     * Release a resource handle
     * @param resourceHandle The resource handle
     */
    void releaseResource(ResourceHandle resourceHandle);
};

#include "ResourceManager.tpp"

#endif //TRUCKER_GAME_RESOURCEMANAGER_H

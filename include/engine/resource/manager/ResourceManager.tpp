
template<typename T, typename... Args>
void ResourceManager::registerResourceResolver(Args&&... args) {
    mResourceResolvers[ResolverIDMapper<T>().getId()] = new T (args...);
}

template<typename T>
ResourceHandle ResourceManager::acquireHandle(std::string path) {
    auto resolverId = ResolverIDMapper<T>().getId();
    auto* resolver = reinterpret_cast<ResourceResolver<T>*>(mResourceResolvers[resolverId]);
    auto resSignature = ResourceSignature(path, resolverId);

    if (mHandleMap.contains(resSignature)) {
        // Resource already loaded
        ResourceHandle handle = mHandleMap[resSignature];
        mRefCount[handle]++;
        return handle;
    }

    auto handle = mAvailableHandles.front();
    mAvailableHandles.pop();

    // Resolve resource
    mResources[handle] = new T(std::move(resolver->resolveResource(path)));
    // Save handle
    mHandleMap[resSignature] = handle;
    // Establish initial ref count
    mRefCount[handle] = 1;
    return handle;
}

template<typename T>
T* ResourceManager::getResource(ResourceHandle resourceHandle) {
   if (mRefCount[resourceHandle] == 0 || resourceHandle >= MAX_RESOURCES) {
       throw std::invalid_argument("Invalid resource access");
   }
   return dynamic_cast<T*>(mResources[resourceHandle]);
}

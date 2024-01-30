#include "Types.h"
#include "Component.h"
#include "ECS.h"

template<class C>
ComponentSignature ECS::registerComponent() {
    const ComponentSignature id = Component<C>().getComponentTypeId();
    if (mComponents.contains(id)) {
        const std::string msg = "Component already registered: ";
        throw std::invalid_argument(msg + typeid(C).name());
    }
    mComponents[id] = new Component<C>;
    return id;
}

template<class C>
C* ECS::getComponent(Entity entity) {
    if (!mEntityArchetypeMap.contains(entity)) {
        std::string msg = "Entity " + std::to_string(entity) + " does not exist";
        throw std::invalid_argument(msg);
    }
    auto ref = mEntityArchetypeMap[entity];
    ComponentSignature signature = Component<C>().getComponentTypeId();
    if (!mComponents.contains(signature)) {
        std::string msg = "Entity " + std::to_string(entity) + " does not have component ";
        throw std::invalid_argument(msg + typeid(C).name());
    }
    ComponentBase* comp = mComponents[signature];
    return reinterpret_cast<C*>(ref.archetype->mComponentData[signature] + comp->GetSize() * ref.index);
}

template<class C>
void ECS::verifyComponentRegistered(ComponentSignature signature) {
    if (!mComponents.contains(signature)) {
        const std::string msg = "Component not registered: ";
        throw std::invalid_argument(msg + typeid(C).name());
    }
}

template<class C>
void ECS::verifyEntityDoesNotHaveComponent(Entity entity, std::optional<EntityArchetypeReference> currentArchetype,
                                           ComponentSignature componentTypeId) {
    if (currentArchetype.has_value() && (currentArchetype.value().archetype->mSignature & componentTypeId) != 0) {
        const std::string msg = "Entity " + std::to_string(entity) + " already has component ";
        throw std::invalid_argument(msg + typeid(C).name());
    }
}

template<class C>
void ECS::verifyEntityHasComponent(Entity entity, ComponentSignature componentTypeId) {
    if ((mEntityArchetypeMap[entity].archetype->mSignature & componentTypeId) == 0) {
        const std::string msg = "Entity " + std::to_string(entity) + " does not have component ";
        throw std::invalid_argument(msg + typeid(C).name());
    }
}

template<class C>
void ECS::removeComponent(Entity entity) {
    auto componentTypeId = Component<C>().getComponentTypeId();

    verifyComponentRegistered<C>(componentTypeId);
    verifyEntityHasComponent<C>(entity, componentTypeId);

    EntityArchetypeReference ref = mEntityArchetypeMap[entity];
    Archetype* newArchetype = getArchetype(ref.archetype->mSignature & componentTypeId.flip());
    ensureCapacity(newArchetype, newArchetype->mCapacity + 1);

    moveEntity(ref.archetype, ref.index, newArchetype);
    if (ref.archetype->mEntities.empty()) {
        deleteArchetype(ref.archetype);
    }
}

template<typename K, typename V>
std::optional<V> findInMap(std::unordered_map<K, V> map, K key) {
    auto iter = map.find(key);
    if (iter == map.end()) {
        return std::optional<V>();
    } else {
        return std::optional<V>(iter->second);
    }
}

template<class C, typename... Args>
void ECS::addComponent(Entity entity, Args &&... args) {
    auto componentTypeId = Component<C>().getComponentTypeId();
    verifyComponentRegistered<C>(componentTypeId);

    ComponentBase* comp = mComponents[componentTypeId];
    auto currentArchetype = findInMap(mEntityArchetypeMap, entity);

    verifyEntityDoesNotHaveComponent<C>(entity, currentArchetype, componentTypeId);

    ArchetypeSignature sig = componentTypeId;
    if (currentArchetype.has_value()) {
        sig |= currentArchetype.value().archetype->mSignature;
    }

    auto newArchetype = getArchetype(sig);
    ensureCapacity(newArchetype, newArchetype->mCapacity + 1);

    if (currentArchetype.has_value()) {
        moveEntity(currentArchetype.value().archetype, currentArchetype.value().index, newArchetype);
        if (currentArchetype.value().archetype->mEntities.empty()) {
            deleteArchetype(currentArchetype.value().archetype);
        }
    } else {
        mEntityArchetypeMap[entity] = {newArchetype, newArchetype->mEntities.size()};
        newArchetype->mEntities.push_back(entity);
    }
    new(newArchetype->mComponentData[componentTypeId] + (newArchetype->mEntities.size() - 1) * comp->GetSize()) C(args...);
}
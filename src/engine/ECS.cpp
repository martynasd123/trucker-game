#include "engine/ECS.h"
#include <algorithm>

Entity ECS::createEntity() {
    return mNextEntityId++;
}

Archetype *ECS::getArchetype(ArchetypeSignature signature) {
    for (const auto &archetype: mArchetypes) {
        if (archetype->mSignature == signature) {
            return archetype;
        }
    }
    // Archetype with given signature does not exist - create a new one
    auto newArchetype = new Archetype;
    newArchetype->mSignature = signature;
    mArchetypes.push_back(newArchetype);
    return newArchetype;
}

void ECS::ensureCapacity(Archetype *archetype, size_t desiredCapacity) {
    if (archetype->mCapacity >= desiredCapacity) {
        return;
    }
    size_t newSize = std::max(size_t (1), archetype->mCapacity);
    while (newSize < desiredCapacity) {
        newSize *=2;
    }
    if (archetype->mEntities.empty()) {
        for (ComponentSignature sig = 1; sig != (ComponentSignature (1) << MAX_COMPONENTS); sig = sig << 1) {
            if ((sig & archetype->mSignature) == 0) {
                continue;
            }
            archetype->mComponentData[sig] = new char[newSize * mComponents[sig]->GetSize()];
        }
        archetype->mCapacity = newSize;
        return;
    }

    for (const auto &item: archetype->mComponentData) {
        auto component = mComponents[item.first];
        size_t componentSize = component->GetSize();
        char* newData = new char[newSize * componentSize];
        for (int i = 0; i < archetype->mEntities.size(); ++i) {
            size_t offset = i * componentSize;
            component->MoveData(item.second + offset, newData + offset);
            component->DestroyData(item.second + offset);
        }
        delete[] item.second;
        archetype->mComponentData[item.first] = newData;
    }
    archetype->mCapacity = newSize;
}

void ECS::moveEntity(Archetype *from, size_t index, Archetype *to) {
    Entity entity = from->mEntities[index];

    // Entity is being moved to the end of the target archetype. Update index in the entity component reference
    mEntityArchetypeMap[entity].index = to->mEntities.size();
    mEntityArchetypeMap[entity].archetype = to;
    if (entity != from->mEntities.back()) {
        // If entity was not last in the source archetype, the last entity will be moved in its place
        mEntityArchetypeMap[from->mEntities.back()].index = index;
    }

    for (const auto &item: from->mComponentData) {
        ComponentBase* component = mComponents[item.first];

        // The offset (in bytes) of component in the old components array
        const size_t oldOffset = index * component->GetSize();
        // The offset (in bytes) of component in the new components array
        const size_t newOffset = to -> mEntities.size() * component->GetSize();

        if (to->mComponentData.contains(item.first)) {
            // Component type does exists in target archetype
            // Move component from old archetype to the new one
            component->MoveData(item.second + oldOffset, to->mComponentData[item.first] + newOffset);
        }

        component->DestroyData(item.second + oldOffset);

        if (entity != from->mEntities.back()) {
            // Move last component in the array in place of the last one
            const size_t lastComponentOffset = component->GetSize() * (from->mEntities.size() - 1);
            component->MoveData(item.second + lastComponentOffset, item.second + oldOffset);
            component->DestroyData(item.second + lastComponentOffset);
        }
    }
    if (entity != from->mEntities.back()) {
        from->mEntities[index] = from->mEntities.back();
    }
    from->mEntities.pop_back();
    to->mEntities.push_back(entity);
}

void ECS::deleteArchetype(Archetype *archetype) {
    for (int i = 0; i < mArchetypes.size(); ++i) {
        if (mArchetypes[i]->mSignature == archetype->mSignature) {
            mArchetypes.erase(mArchetypes.begin() + i);
            delete archetype;
            return;
        }
    }
}

void ECS::runSystems(SystemLayer layer, float dt) {
    for (const auto &entry: mSystemEntries) {
        if ((entry.layer & layer) != 0) {
            for (const auto &archetype: mArchetypes) {
                if ((archetype->mSignature & entry.system->mSignature) != 0) {
                    entry.system->update(dt, archetype->mEntities);
                }
            }
        }
    }
}

ECS::~ECS() {
    for (const auto &archetype: mArchetypes) {
        for (const auto &componentEntry: archetype->mComponentData) {
            ComponentBase* comp = mComponents[componentEntry.first];
            for (int i = 0; i < archetype->mEntities.size(); ++i) {
                char* ptr = componentEntry.second + (comp->GetSize() * i);
                comp->DestroyData(ptr);
                delete ptr;
            }
        }
        delete archetype;
    }
    for (const auto &item: mComponents) {
        delete item.second;
    }
}

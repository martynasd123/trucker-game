#ifndef TRUCKER_GAME_ECS_H
#define TRUCKER_GAME_ECS_H


#include "engine/Types.h"
#include "Component.h"
#include "Archetype.h"
#include "System.h"

class ECS {
private:
    /**
     * Data structure to act as a reference of entity in an archetype
     */
    struct EntityArchetypeReference {
        // Archetype the entity belongs to
        Archetype* archetype;
        // Index of entity in archetype
        size_t index;
    };

    struct SystemEntry {
        SystemBase* system{};
        SystemLayer layer;

        bool operator <(const SystemEntry& e1) const {
            return layer.to_ulong() < e1.layer.to_ulong();
        }
    };

    Entity mNextEntityId = 1;
    std::unordered_map<ComponentSignature, ComponentBase*> mComponents;
    std::unordered_map<Entity, EntityArchetypeReference> mEntityArchetypeMap;
    std::vector<Archetype*> mArchetypes;
    std::vector<SystemEntry> mSystemEntries;

    void ensureCapacity(Archetype *archetype, size_t newCapacity);

    void moveEntity(Archetype *from, size_t index, Archetype *to);

    template<class C>
    void verifyComponentRegistered(ComponentSignature signature);

    template<class C>
    void verifyEntityDoesNotHaveComponent(Entity entity, std::optional<EntityArchetypeReference> currentArchetype,
                                          ComponentSignature componentTypeId);

    template<class C>
    void verifyEntityHasComponent(Entity entity, ComponentSignature componentTypeId);

    void deleteArchetype(Archetype *archetype);

    Archetype *getArchetype(ArchetypeSignature signature);
public:
    /**
     * Assign a new entity ID
     * @return The new entity ID
     */
    Entity createEntity();

    /**
     * Register a new component with the ECS
     * @tparam C Type of component
     * @return Component signature
     */
    template<class C>
    ComponentSignature registerComponent();

    /**
     * Add component to specified entity
     * @tparam C The type of component to add
     * @tparam Args Types of arguments
     * @param entity Entity to add component to
     * @param args Arguments to initialize component with
     */
    template<class C, typename... Args>
    void addComponent(Entity entity, Args &&... args);

    /**
     * Remove component from specified entity
     * @tparam C Type of component to remove
     * @param entity Entity to remove component from
     */
    template<class C>
    void removeComponent(Entity entity);

    /**
     * Get component from a given entity
     * @tparam C Type of component to get
     * @param entity Entity to get component from
     */
    template<class C>
    C* getComponent(Entity entity);

    /**
     * Register a system at a given layer
     * @param layer Layer to register system for
     * @param system System to register
     */
    template<class SystemType, typename = std::is_base_of<System<>, SystemType>>
            void registerSystem(SystemLayer layer, SystemType* system) {
        auto baseRef = dynamic_cast<SystemBase*>(system);
        for (const auto &item: mSystemEntries) {
            if (item.system == baseRef) {
                std::string msg = "System already registered ";
                throw std::invalid_argument(msg + typeid(*system).name());
            }
        }
        mSystemEntries.push_back({baseRef, layer});
        std::sort(mSystemEntries.begin(), mSystemEntries.end());
    }

    /**
     * Run systems of a given layer. Multiple layers can be combined using OR operator
     * @param layer Layers to be run
     * @param dt Time step
     */
    void runSystems(SystemLayer layer, float dt);
};

#include "ECS.tpp"
#endif //TRUCKER_GAME_ECS_H

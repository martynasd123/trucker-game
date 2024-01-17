//
// Created by Martynas Dargis on 17.01.24.
//

#ifndef TRUCKER_GAME_COMPONENTMANAGER_H
#define TRUCKER_GAME_COMPONENTMANAGER_H

#include "Types.h"
#include "ComponentArray.h"

class ComponentManager {
private:
    // Component type to component array map
    std::array<std::shared_ptr<IComponentArray>, MAX_COMPONENTS> m_component_arrays;
    // Component type string to component type ID
    std::unordered_map<std::string, ComponentType> m_component_types;
    // The next component ID to be allocated
    ComponentType m_next_component_type = 0;
    template<typename T> std::shared_ptr<ComponentArray<T>> getComponentArray();
public:
    template<typename T> void addComponent(Entity entity, T component);
    template<typename T> void removeComponent(Entity entity);
    template<typename T> void getComponent(Entity entity);
    template<typename T> void registerComponent();
};


#endif //TRUCKER_GAME_COMPONENTMANAGER_H

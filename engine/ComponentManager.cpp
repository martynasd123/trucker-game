//
// Created by Martynas Dargis on 17.01.24.
//

#include "ComponentManager.h"

#include <cassert>
#include <memory>

template<typename T>
void ComponentManager::addComponent(Entity entity, T component) {
    getComponentArray<T>().addComponent(entity, component);
}

template<typename T>
void ComponentManager::removeComponent(Entity entity) {
    getComponentArray<T>().removeComponent(entity);
}

template<typename T>
void ComponentManager::registerComponent() {
    std::string component_name = typeid(T).name();
    assert(m_component_types.find(component_name) == m_component_types.end() || "Component already registered");
    ComponentType componentType = m_next_component_type++;
    m_component_types[component_name] = componentType;
    m_component_arrays[componentType] = std::make_shared<ComponentArray<T>>();
}

template<typename T>
void ComponentManager::getComponent(Entity entity) {
    return getComponentArray<T>().getComponent(entity);
}

template<typename T>
std::shared_ptr<ComponentArray<T>> ComponentManager::getComponentArray() {
    std::string component_name = typeid(T).name();
    assert (m_component_types.find(component_name) != m_component_types.end() || "Component not registered");
    return m_component_arrays[m_component_types[component_name]];
}
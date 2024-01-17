//
// Created by Martynas Dargis on 17.01.24.
//

#ifndef TRUCKER_GAME_COMPONENTARRAY_H
#define TRUCKER_GAME_COMPONENTARRAY_H

#include "Types.h"

class IComponentArray {
public:
    virtual void entityDeleted(Entity entity) = 0;
};

template<typename T>
class ComponentArray : public IComponentArray {
private:
    std::array<T, MAX_ENTITIES> m_components;
public:
    T getComponent(Entity entity);
    void addComponent(Entity entity, T component);
    void removeComponent(Entity entity);
    void entityDeleted(Entity entity) override;
};


#endif //TRUCKER_GAME_COMPONENTARRAY_H

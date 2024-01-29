#ifndef TRUCKER_GAME_COMPONENT_H
#define TRUCKER_GAME_COMPONENT_H


#include "Types.h"

class ComponentBase {
protected:
    static ComponentSignature mLastComponentTypeId;
public:
    virtual int GetSize() = 0;
    virtual void DestroyData(char* loc) = 0;
    virtual void Initialize(char* loc) = 0;
    virtual void MoveData(char* src, char* dst) = 0;
    virtual ~ComponentBase() = default;
};

template<class C>
class Component : public ComponentBase {
public:
    int GetSize() override;
    void DestroyData(char *loc) override;
    void Initialize(char *loc) override;
    void MoveData(char *src, char *dst) override;
    ComponentSignature getComponentTypeId() {
        static const std::bitset<MAX_COMPONENTS> id = (mLastComponentTypeId == 0)
                                                      ? (mLastComponentTypeId = 1)
                                                      : (mLastComponentTypeId << 1);
        return id;
    }
    ~Component() override = default;
};

#include "Component.tpp"

#endif //TRUCKER_GAME_COMPONENT_H

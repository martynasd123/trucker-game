#ifndef TRUCKER_GAME_SYSTEM_H
#define TRUCKER_GAME_SYSTEM_H

#include "Types.h"

class SystemBase {
protected:
    explicit SystemBase(SystemSignature signature) : mSignature(signature) {}
public:
    const SystemSignature mSignature;
    virtual void update(long dt, std::vector<Entity> entities) = 0;
    virtual void entityRemoved(Entity entity) = 0;
    virtual void entityAdded(Entity entity) = 0;
    virtual void init() = 0;
    const bool doesCareAbout(ArchetypeSignature archetypeSignature) {
        return (archetypeSignature & mSignature) == mSignature;
    }
};

template<class... C>
class System : public SystemBase {
private:
    template<std::size_t Index>
    std::enable_if_t<Index != sizeof...(C), SystemSignature>
            generateSignature() {
        using type = std::tuple_element_t<Index, std::tuple<C...>>;
        return Component<type>().getComponentTypeId() | generateSignature<Index + 1>();
    }

    template<std::size_t Index>
    std::enable_if_t<Index == sizeof...(C), SystemSignature>
            generateSignature() {
        return ComponentSignature(0);
    }

public:
    System() : SystemBase(generateSignature<0>()) {}
};


#endif //TRUCKER_GAME_SYSTEM_H

#ifndef TRUCKER_GAME_MATERIALHANDLERREGISTRY_H
#define TRUCKER_GAME_MATERIALHANDLERREGISTRY_H

#include "MaterialHandler.h"
#include <type_traits>

class MaterialHandlerRegistry {
private:
    unordered_map<std::string, MaterialHandler&> mMaterialHandlers;
public:

    const MaterialHandler& getHandler(const string& materialType);

    template <typename HandlerType, typename... Args,
            typename std::enable_if_t<std::is_base_of<MaterialHandler, HandlerType>::value, int> = 0>
    void registerHandler(Args&&... arguments) {
        auto* handler = new HandlerType(std::forward<Args>(arguments)...);
        auto& base = *dynamic_cast<MaterialHandler*>(handler);
        std::string key = base.getMaterialTypeName();
        mMaterialHandlers.emplace(key, base);
    }

    const vector<const MaterialHandler*> getHandlers();

};


#endif //TRUCKER_GAME_MATERIALHANDLERREGISTRY_H

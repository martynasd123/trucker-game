#ifndef TRUCKER_GAME_BPMONOCHROMATICMATERIALHANDLER_H
#define TRUCKER_GAME_BPMONOCHROMATICMATERIALHANDLER_H

#include "MaterialHandlerBase.h"

class BPMonochromaticMaterialHandler: public MaterialHandlerBase {
public:
    explicit BPMonochromaticMaterialHandler(ResourceManager &resManager);

    [[nodiscard]] std::string getMaterialTypeName() const override;

};


#endif //TRUCKER_GAME_BPMONOCHROMATICMATERIALHANDLER_H

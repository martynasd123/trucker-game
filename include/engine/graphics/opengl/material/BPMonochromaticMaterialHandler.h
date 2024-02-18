#ifndef TRUCKER_GAME_BPMONOCHROMATICMATERIALHANDLER_H
#define TRUCKER_GAME_BPMONOCHROMATICMATERIALHANDLER_H

#include "MaterialHandlerBase.h"

class BPMonochromaticMaterialHandler: public MaterialHandlerBase<BPMonochromaticMaterial> {
public:
    explicit BPMonochromaticMaterialHandler(ResourceManager &resManager);

    std::string getMaterialTypeName() const override;

    unsigned int getUBOMaterialSize() const override;

    void writeToUniformBuffer(vector<BPMonochromaticMaterial> materials, int offset, BufferObjectBase& buff) const override;

};


#endif //TRUCKER_GAME_BPMONOCHROMATICMATERIALHANDLER_H

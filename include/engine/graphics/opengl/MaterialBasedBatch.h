#ifndef TRUCKER_GAME_MATERIALBASEDBATCH_H
#define TRUCKER_GAME_MATERIALBASEDBATCH_H

#include "Batch.h"

class MaterialBasedBatch: public Batch {
public:
    virtual void draw() = 0;
};

#endif //TRUCKER_GAME_MATERIALBASEDBATCH_H

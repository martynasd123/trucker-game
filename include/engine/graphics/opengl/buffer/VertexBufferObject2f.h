#ifndef TRUCKER_GAME_VERTEXBUFFEROBJECT2F_H
#define TRUCKER_GAME_VERTEXBUFFEROBJECT2F_H

#include "VertexBufferObject.h"
#include "common/math/Vector2f.h"

class VertexBufferObject2f: public VertexBufferObject<Vector2f> {
protected:
    void allocateBuffer(int size) override;
public:
    void setData(vector<Vector2f>::iterator begin, vector<Vector2f>::iterator end, unsigned int offset) override;
};


#endif //TRUCKER_GAME_VERTEXBUFFEROBJECT2F_H

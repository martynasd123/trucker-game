#ifndef TRUCKER_GAME_VERTEXBUFFEROBJECT3F_H
#define TRUCKER_GAME_VERTEXBUFFEROBJECT3F_H

#include "VertexBufferObject.h"
#include "common/math/Vector3f.h"

class VertexBufferObject3f: public VertexBufferObject<Vector3f> {
protected:
    void allocateBuffer(int size) override;
public:
    void setData(vector<Vector3f>::iterator begin, vector<Vector3f>::iterator end, unsigned int offset) override;
};


#endif //TRUCKER_GAME_VERTEXBUFFEROBJECT3F_H

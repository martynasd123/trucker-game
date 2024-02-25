#ifndef TRUCKER_GAME_BUFFEROBJECT_H
#define TRUCKER_GAME_BUFFEROBJECT_H

#include <glad/glad.h>
#include <vector>
#include <optional>
#include "common/math/Vector3f.h"
#include "common/math/Vector2f.h"
#include "engine/graphics/opengl/util/GLUtils.h"
#include "common/render/Light.h"

using namespace std;

class BufferObjectBase {
protected:
    GLuint mId{};
    GLenum mType;
    unsigned int mSize;

    explicit BufferObjectBase(int size, GLenum type);

public:
    void setData(char *begin, unsigned int size, unsigned int offset);

    void bind();

    void unbind();
};

template<typename T>
class BufferObject : public BufferObjectBase {
protected:
    explicit BufferObject(int size, GLenum type) : BufferObjectBase(size, type) {
        bind();
        allocateBuffer(size);
        unbind();
    }

public:
    void setData(vector<T>::iterator begin, vector<T>::iterator end, unsigned int offset);

    void allocateBuffer(int size);

    GLenum getType() {
        return mType;
    }
};

template<typename T>
void BufferObject<T>::setData(vector<T>::iterator begin, vector<T>::iterator end, unsigned int offset) {
    T data[distance(begin, end)];
    int i = 0;
    for (auto it = begin; it < end; it++) {
        data[i++] = *it;
    }
    bind();
    glBufferSubData(mType, offset * sizeof(T), i * sizeof(T), &data);
    unbind();
}

template<typename T>
void BufferObject<T>::allocateBuffer(int size) {
    glBufferData(mType, size * sizeof(T), nullptr, GL_DYNAMIC_DRAW);
}

template<typename T>
class VertexBufferObject : public BufferObject<T> {
public:
    explicit VertexBufferObject(int size) : BufferObject<T>(size, GL_ARRAY_BUFFER) {}
};

class ElementBufferObject : public BufferObject<unsigned int> {
public:
    explicit ElementBufferObject(int size) : BufferObject<unsigned int>(size, GL_ELEMENT_ARRAY_BUFFER) {}
};

class UniformBufferObject : public BufferObjectBase {
public:
    explicit UniformBufferObject(int size);

    void bindToPoint(unsigned int bindingPoint) {
        this->bind();
        glBindBufferBase(this->mType, bindingPoint, mId);
        this->unbind();
    }
};

template<typename LightType>
void setLightAtIndex(unsigned int index, const LightType &light, BufferObjectBase& buff);

template<typename LightType>
unsigned int getLightStructureSize();

template<class LightType>
class LightsUniformBufferObject : public UniformBufferObject {
private:
    vector<unsigned int> items;
    vector<LightType> lights;
    unsigned int maxNumLights;
public:
    LightsUniformBufferObject(unsigned int maxNumLights):UniformBufferObject(getLightStructureSize<LightType>() * maxNumLights),
        maxNumLights(maxNumLights){
    }

    void addLight(unsigned int id, LightType &light) {
        setLightAtIndex(items.size(), light, *dynamic_cast<BufferObjectBase*>(this));
        items.push_back(id);
        lights.push_back(LightType(light));
    }

    void removeLight(unsigned int id) {
        for (int i = 0; i < maxNumLights; ++i) {
            if (items[i] == id) {
                int structureSize = getLightStructureSize<LightType>();
                if (i - 1 == maxNumLights || items.size() == 1) {
                    return;
                }
                setLightAtIndex(i, lights.back(), *dynamic_cast<BufferObjectBase*>(this));
                items[i] = items.back();
                lights[i] = lights.back();
                items.pop_back();
                lights.pop_back();
            }
        }
    }

    unsigned int getNumLights() {
        return items.size();
    }

};

#endif //TRUCKER_GAME_BUFFEROBJECT_H

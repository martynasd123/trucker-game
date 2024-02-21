#include "engine/graphics/opengl/buffer/BufferObject.h"

template<>
void BufferObject<Vector3f>::setData(vector<Vector3f>::iterator begin, vector<Vector3f>::iterator end, unsigned int offset) {
    float vectors[distance(begin, end) * 3];
    int i = 0;
    for (auto it = begin; it < end; it++) {
        vectors[i++] = it->getX();
        vectors[i++] = it->getY();
        vectors[i++] = it->getZ();
    }
    bind();
    glBufferSubData(mType, offset * sizeof(float) * 3, i * sizeof(float), &vectors);
    unbind();
}

template<> void BufferObject<Vector3f>::allocateBuffer(int size) {
    glBufferData(mType, size * sizeof(float) * 3, nullptr, GL_DYNAMIC_DRAW);
}

template<>
void BufferObject<Vector2f>::setData(vector<Vector2f>::iterator begin, vector<Vector2f>::iterator end, unsigned int offset) {
    float vectors[distance(begin, end) * 2];
    int i = 0;
    for (auto it = begin; it < end; it++) {
        vectors[i++] = it->getX();
        vectors[i++] = it->getY();
    }
    bind();
    glBufferSubData(mType, offset * sizeof(float) * 2, i * sizeof(float), &vectors);
    unbind();
}

template<> void BufferObject<Vector2f>::allocateBuffer(int size) {
    glBufferData(mType, size * sizeof(float) * 2, nullptr, GL_DYNAMIC_DRAW);
}

template<>
void BufferObject<unsigned int>::setData(vector<unsigned int>::iterator begin, vector<unsigned int>::iterator end, unsigned int offset) {
    unsigned int elements[distance(begin, end)];
    int i = 0;
    for (auto it = begin; it != end; it++) {
        elements[i++] = *it;
    }
    bind();
    glBufferSubData(mType, offset * sizeof(unsigned int), i * sizeof(unsigned int), &elements);
    unbind();
}

template<> void BufferObject<unsigned int>::allocateBuffer(int size) {
    glBufferData(mType, size * sizeof(unsigned int), nullptr, GL_DYNAMIC_DRAW);
}

void BufferObjectBase::setData(char *begin, unsigned int size, unsigned int offset) {
    GL_UTIL::checkError();
    bind();
    glBufferSubData(mType, offset, size, (void*)begin);
    unbind();
    GL_UTIL::checkError();
}

void BufferObjectBase::bind()  {
    glBindBuffer(mType, mId);
}

void BufferObjectBase::unbind() {
    glBindBuffer(mType, 0);
}

BufferObjectBase::BufferObjectBase(int size, GLenum type): mType(type) {
    this->mSize = size;
    glGenBuffers(1, &mId);
}

UniformBufferObject::UniformBufferObject(int size): BufferObjectBase(size, GL_UNIFORM_BUFFER) {
    bind();
    glBufferData(mType, size, nullptr, GL_DYNAMIC_DRAW);
    unbind();
}

struct std140PointLight {
    float colorX;
    float colorY;
    float colorZ;
    float intensity;
    float positionX;
    float positionY;
    float positionZ;
    float pad0;

    explicit std140PointLight(const PointLight &light) :
            colorX(light.color.getX()),
            colorY(light.color.getY()),
            colorZ(light.color.getZ()),
            intensity(light.intensity),
            positionX(light.color.getZ()),
            positionY(light.color.getY()),
            positionZ(light.color.getZ()) {}
};

struct std140Light {
    float colorX;
    float colorY;
    float colorZ;
    float intensity;

    explicit std140Light(const Light &light) :
            colorX(light.color.getX()),
            colorY(light.color.getY()),
            colorZ(light.color.getZ()),
            intensity(light.intensity){}
};


template<>
void setLightAtIndex(unsigned int index, const PointLight &light, BufferObjectBase& buff) {
    std140PointLight std140(light);
    buff.setData((char*)&std140, sizeof(std140PointLight), sizeof(std140PointLight) * index);
}

template<>
void setLightAtIndex(unsigned int index, const Light &light, BufferObjectBase& buff) {
    std140Light std140(light);
    buff.setData((char*)&std140, sizeof(std140Light), sizeof(std140Light) * index);
}

template<>
unsigned int getLightStructureSize<PointLight>() {
    return sizeof(std140PointLight);
}

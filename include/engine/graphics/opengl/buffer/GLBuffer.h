#ifndef TRUCKER_GAME_GLBUFFER_H
#define TRUCKER_GAME_GLBUFFER_H

#include "glad/glad.h"

#include <memory>
#include <vector>

#include "engine/graphics/opengl/VertexArrayObject.h"

using namespace std;

enum DataPackingStrategyType {
    TIGHTLY_PACKED,
    STD140
};

template<typename T>
static GLenum toGLEnum(T value);

enum BufferUsage {
    DYNAMIC_DRAW,
    STATIC_DRAW,
    STREAM_DRAW,
};

template<>
GLenum toGLEnum(BufferUsage bu) {
    switch (bu) {
        case DYNAMIC_DRAW:
            return GL_DYNAMIC_DRAW;
        case STATIC_DRAW:
            return GL_STATIC_DRAW;
        case STREAM_DRAW:
            return GL_STREAM_DRAW;
    }
    throw invalid_argument("Unexpected buffer usage value");
}

enum BufferType {
    UNIFORM_BUFFER,
    ARRAY_BUFFER,
    ELEMENT_BUFFER
};

template<>
GLenum toGLEnum(BufferType bt) {
    switch (bt) {
        case UNIFORM_BUFFER:
            return GL_UNIFORM_BUFFER;
        case ARRAY_BUFFER:
            return GL_ARRAY_BUFFER;
        case ELEMENT_BUFFER:
            return GL_ELEMENT_ARRAY_BUFFER;
    }
    throw invalid_argument("Unexpected buffer type value");
}

enum PrimitiveType {
    FLOAT,
    INT,
    UINT
};

template<>
GLenum toGLEnum(PrimitiveType tp) {
    switch (tp) {
        case FLOAT:
            return GL_FLOAT;
        case INT:
            return GL_INT;
        case UINT:
            return GL_UNSIGNED_INT;
    }
    throw invalid_argument("Unexpected primitive type value");
}

template<DataPackingStrategyType Strategy, class DataType>
class DataPackingStrategy {
public:
    static size_t getElementSize();

    static PrimitiveType getPrimitiveType();

    static unsigned int getPrimitiveTypeSize();

    template<class Iterable>
    static void serializeData(Iterable begin, Iterable end, char *destination);
};

static GLuint generateBuffer() {
    GLuint id;
    glGenBuffers(1, &id);
    return id;
}

static void deleteBuffer(GLuint *id) {
    glDeleteBuffers(1, id);
    delete id;
}

class GLBuffer {
protected:
    shared_ptr<GLuint> mId;
    BufferType mType;
    BufferUsage mUsage;
    GLuint mSize;
public:
    GLBuffer(BufferType type, GLuint size, BufferUsage usage) :
            mType(type),
            mSize(size),
            mUsage(usage),
            mId(new GLuint(generateBuffer()), deleteBuffer) {
        bind();
        glBufferData(toGLEnum(mType), size, nullptr, toGLEnum(usage));
        unbind();
    }

    void bind() const {
        glBindBuffer(toGLEnum(mType), *mId);
    }

    void unbind() const {
        glBindBuffer(toGLEnum(mType), 0);
    }

    void setDataRaw(char *data, unsigned int length, unsigned int offset) {
        bind();
        glBufferSubData(toGLEnum(mType), offset, length, data);
        unbind();
    }

    virtual void attachToVertexArrayObject(unsigned int index, const VertexArrayObject &vao) = 0;

    void attachToVertexArrayObjectAsElementBuffer(const VertexArrayObject &vao) {
        if (mType != ELEMENT_BUFFER) {
            throw invalid_argument("Buffer of this type cannot be attached to vao as element buffer");
        }
        vao.bind();
        bind();
        vao.unbind();
        unbind();
    }

    void bindAsUniformBufferObject(unsigned int bindingPoint) {
        if (mType != UNIFORM_BUFFER) {
            throw invalid_argument("Buffer of this type cannot be bound as to uniform block binding point");
        }
        bind();
        glBindBufferBase(toGLEnum(mType), bindingPoint, *mId);
        unbind();
    }

    [[nodiscard]] BufferType getType() const {
        return mType;
    }

    [[nodiscard]] BufferUsage getUsage() const {
        return mUsage;
    }

};

template<class DataType, DataPackingStrategyType PackingStrategy>
class GLBufferArray : public GLBuffer {
private:
    DataPackingStrategy<PackingStrategy, DataType> mPackingStrategy{};
public:
    GLBufferArray(BufferType type, GLuint size, BufferUsage usage) :
            GLBuffer(type, DataPackingStrategy<PackingStrategy, DataType>().getElementSize() * size, usage) {}

    template<class Iterator>
    void setData(Iterator begin, Iterator end, size_t index) {
        size_t elementSize = mPackingStrategy.getElementSize();
        size_t numElements = distance(begin, end);
        if ((index + numElements) * elementSize > mSize) {
            throw runtime_error("Buffer overflow");
        }

        char *dst = new char[elementSize * numElements];
        mPackingStrategy.serializeData(begin, end, dst);
        setDataRaw(dst, elementSize * numElements, index * elementSize);
        delete[] dst;
    }

    void setDataSingle(const DataType &element, size_t index) {
        size_t elementSize = mPackingStrategy.getElementSize();
        char *dst = new char[elementSize];
        mPackingStrategy.serializeData(&element, &element + 1, dst);
        setDataRaw(dst, elementSize, index * elementSize);
        delete[] dst;
    }

    void attachToVertexArrayObject(unsigned int index, const VertexArrayObject &vao) override {
        if (mType != ARRAY_BUFFER) {
            throw invalid_argument("Buffer of this type cannot be attached to vao");
        }
        vao.bind();
        bind();
        glVertexAttribPointer(index, mPackingStrategy.getPrimitiveTypeSize(),
                              toGLEnum(mPackingStrategy.getPrimitiveType()),
                              GL_FALSE, 0, nullptr);
        glEnableVertexAttribArray(index);
        vao.unbind();
        unbind();
    }

};

template<class DataType>
class GLBufferArrayList {
private:
    GLBufferArray<DataType, STD140> mBufferArray;
    vector<DataType> mData;
    size_t mCapacity;
public:
    GLBufferArrayList(BufferType type, GLuint initialCapacity, BufferUsage usage) :
            mData(),
            mCapacity(initialCapacity),
            mBufferArray(GLBufferArray<DataType, STD140>(type, initialCapacity, usage)) {
    }

    void addElement(const DataType &element) {
        mData.emplace_back(element);
        if (mData.size() > mCapacity) {
            mBufferArray = GLBufferArray<DataType, STD140>(mBufferArray.getType(), mCapacity *= 2, mBufferArray.getUsage());
            mBufferArray.setData(mData.begin(), mData.end(), 0);
        } else {
            mBufferArray.setDataSingle(element, mData.size() - 1);
        }
    }

    void removeElement(size_t index) {
        if (index == mData.size() - 1) {
            mData.pop_back();
        } else {
            mBufferArray.setDataSingle(mData.back(), index);
            mData[index] = mData.back();
            mData.pop_back();
        }
    }

    void bindAsUniformBufferObject(unsigned int bindingPoint) {
        mBufferArray.bindAsUniformBufferObject(bindingPoint);
    }


    [[nodiscard]] size_t size() const {
        return mData.size();
    }
};

#include "GLBuffer.tpp"

#endif //TRUCKER_GAME_GLBUFFER_H

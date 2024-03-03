#include <memory>
#include <vector>
#include "GLBuffer.h"
#include "engine/graphics/opengl/buffer/std140.h"

/*
 * Signed integer specialization
 */
template<>
class DataPackingStrategy<TIGHTLY_PACKED, int> {

    static size_t getElementSize() {
        return sizeof(int);
    }

    static PrimitiveType getPrimitiveType() {
        return INT;
    }

    static unsigned int getPrimitiveTypeSize() {
        return 1;
    }

    template<class Iterable>
    std::unique_ptr<char[]> serializeData(Iterable begin, Iterable end, char *dst) const {
        size_t numElements = std::distance(begin, end);
        for (int i = 0; i < numElements; ++i) {
            *(((int *) dst) + i) = *(begin + i);
        }
    }
};


/*
 * Unsigned integer specialization
 */
template<>
class DataPackingStrategy<TIGHTLY_PACKED, unsigned int> {
public:
    static size_t getElementSize() {
        return sizeof(unsigned int);
    }

    static PrimitiveType getPrimitiveType() {
        return UINT;
    }

    static unsigned int getPrimitiveTypeSize() {
        return 1;
    }

    template<class Iterable>
    static void serializeData(Iterable begin, Iterable end, char *dst) {
        size_t numElements = std::distance(begin, end);
        for (int i = 0; i < numElements; ++i) {
            *(((unsigned int *) dst) + i) = *(begin + i);
        }
    }
};

/*
 * Vector2f specialization
 */
template<>
class DataPackingStrategy<TIGHTLY_PACKED, Vector2f> {
public:
    static size_t getElementSize() {
        return sizeof(float) * 2;
    }

    static PrimitiveType getPrimitiveType() {
        return FLOAT;
    }

    static unsigned int getPrimitiveTypeSize() {
        return 2;
    }

    template<class Iterable>
    static void serializeData(Iterable begin, Iterable end, char *dst) {
        size_t numElements = std::distance(begin, end);
        for (int i = 0; i < numElements; ++i) {
            const Vector2f &vec = *(begin + i);
            *(((float *) dst) + (i * 2)) = vec.getX();
            *(((float *) dst) + (i * 2) + 1) = vec.getY();
        }
    }
};

/*
 * Vector3f specialization
 */
template<>
class DataPackingStrategy<TIGHTLY_PACKED, Vector3f> {
public:
    static size_t getElementSize() {
        return sizeof(float) * 3;
    }

    static PrimitiveType getPrimitiveType() {
        return FLOAT;
    }

    static unsigned int getPrimitiveTypeSize() {
        return 3;
    }

    template<class Iterable>
    static void serializeData(Iterable begin, Iterable end, char *dst) {
        size_t numElements = std::distance(begin, end);
        for (int i = 0; i < numElements; ++i) {
            const Vector3f &vec = *(begin + i);
            *(((float *) dst) + (i * 3)) = vec.getX();
            *(((float *) dst) + (i * 3) + 1) = vec.getY();
            *(((float *) dst) + (i * 3) + 2) = vec.getZ();
        }
    }
};

/**
 * BPMonochromaticMaterial specialization
 */
template<>
class DataPackingStrategy<STD140, BPMonochromaticMaterial> {
public:
    static size_t getElementSize() {
        return sizeof(std140BPMonoChromaticMaterial);
    }

    static PrimitiveType getPrimitiveType() {
        throw runtime_error("Unsupported operation");
    }

    static unsigned int getPrimitiveTypeSize() {
        throw runtime_error("Unsupported operation");
    }

    template<class Iterable>
    static void serializeData(Iterable begin, Iterable end, char *dst) {
        const int numElements = distance(begin, end);
        auto* destination = reinterpret_cast<std140BPMonoChromaticMaterial*>(std::launder(dst));

        for (int i = 0; i < numElements; ++i) {
            BPMonochromaticMaterial& mat = *(begin + i);
            auto std140mat = std140BPMonoChromaticMaterial();
            std140mat.specularX = mat.specular.getX();
            std140mat.specularY = mat.specular.getY();
            std140mat.specularZ = mat.specular.getZ();
            std140mat.colorX = mat.color.getX();
            std140mat.colorY = mat.color.getY();
            std140mat.colorZ = mat.color.getZ();
            std140mat.ambient = mat.ambient;
            std140mat.diffuse = mat.diffuse;
            std140mat.shininess = mat.shininess;
            destination[i] = std140mat;
        }
    }
};


/**
 * PointLight specialization
 */
template<>
class DataPackingStrategy<STD140, PointLight> {
public:
    static size_t getElementSize() {
        return sizeof(std140PointLight);
    }

    static PrimitiveType getPrimitiveType() {
        throw runtime_error("Unsupported operation");
    }

    static unsigned int getPrimitiveTypeSize() {
        throw runtime_error("Unsupported operation");
    }

    template<class Iterable>
    static void serializeData(Iterable begin, Iterable end, char *dst) {
        const int numElements = distance(begin, end);
        auto* destination = reinterpret_cast<std140PointLight*>(std::launder(dst));

        for (int i = 0; i < numElements; ++i) {
            destination[i] = std140PointLight(*(begin + i));
        }
    }
};
#ifndef TRUCKER_GAME_MESH_H
#define TRUCKER_GAME_MESH_H

#include "common/math/Vector3f.h"
#include "common/math/Vector2f.h"
#include "engine/resource/Types.h"
#include "common/render/Material.h"
#include <utility>
#include <vector>

using namespace std;

struct Vertex {
    int positionIndex;
    int normalIndex;
    int uvIndex;

    Vertex(int positionIndex, int normalIndex, int uvIndex) : positionIndex(positionIndex), normalIndex(normalIndex),
                                                              uvIndex(uvIndex) {}
};

struct Triangle {
    Vertex vertices[3];
    Triangle(Vertex v1, Vertex v2, Vertex v3)
            : vertices{v1, v2, v3} {
    }
};

struct Group {
    // Each element is an index of the mesh primitives array
    vector<int> primitives;
    std::string name;

    Group(const vector<int> &primitives, string name) : primitives(primitives), name(std::move(name)) {}
};

struct GroupMapping {
    vector<std::string> groups;

    explicit GroupMapping(const vector<std::string> &groups) : groups(groups) {}
};

struct Mesh {
    vector<Vector3f> positions;
    vector<Vector3f> normals;
    vector<Vector2f> uvCoordinates;
    // List of triangles, each defined by three vertices
    vector<Triangle> primitives;
    // List of primitive groups
    vector<Group> groups;
    // List of materials
    vector<Material*> materials;
    // Each element maps nth material to the list of groups
    vector<GroupMapping> materialMappings;

    template<typename T, typename... Args>
    void addMaterial(Args&&... args) {
        T* ref = new T(args...);
        materials.push_back(ref);
    }

    virtual ~Mesh() {
        for (const auto &mat: materials) {
            delete mat;
        }
    }
};

#endif //TRUCKER_GAME_MESH_H

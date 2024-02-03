#ifndef TRUCKER_GAME_MESH_H
#define TRUCKER_GAME_MESH_H

#include "common/math/Vector3f.h"
#include "common/math/Vector2f.h"
#include "engine/resource/Types.h"
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

struct Mesh {
    vector<Vector3f> positions;
    vector<Vector3f> normals;
    vector<Vector2f> uvCoordinates;
    // List of materials
    vector<ResourcePath> materials;
    // Each nth outer vector element corresponds to nth material
    // The inner vector holds all primitives for that material
    vector<vector<Triangle>> indices;
};

#endif //TRUCKER_GAME_MESH_H

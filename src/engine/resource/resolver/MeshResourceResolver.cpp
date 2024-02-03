#include "engine/resource/resolver/MeshResourceResolver.h"
#include <fstream>
#include <nlohmann/json.hpp>

using namespace std;
using namespace nlohmann;

bool isValidCoordinate2f(json coord) {
    return coord.is_array() && coord.size() == 2 && coord[0].is_number_float() && coord[1].is_number_float();
}


bool isValidCoordinate3f(json coord) {
    return coord.is_array() && coord.size() == 3 && coord[0].is_number_float() && coord[1].is_number_float()
        && coord[2].is_number_float();
}

void parsePositions(const json& data, Mesh& mesh, const ResourcePath& resPath) {
    if (!data.contains("positions") || !data["positions"].is_array()) {
        throw runtime_error("No positions array in mesh file " + resPath);
    }
    for (const auto &position: data["positions"]) {
        if (!isValidCoordinate3f(position)) {
            throw runtime_error("Invalid vertex position encountered while parsing " + resPath);
        }
        float x = position[0];
        float y = position[1];
        float z = position[2];
        mesh.positions.emplace_back(x, y, z);
    }
}

void parseNormals(const json& data, Mesh& mesh, const ResourcePath& resPath) {
    if (!data.contains("normals") || !data["normals"].is_array()) {
        return;
    }
    for (const auto &normal: data["normals"]) {
        if (!isValidCoordinate3f(normal)) {
            throw runtime_error("Invalid vertex normal encountered while parsing " + resPath);
        }
        float x = normal[0];
        float y = normal[1];
        float z = normal[2];
        mesh.normals.emplace_back(x, y, z);
    }
}

void parseUVCoordinates(const json& data, Mesh& mesh, const ResourcePath& resPath) {
    if (!data.contains("uv") || !data["uv"].is_array()) {
        return;
    }
    for (const auto &coord: data["uv"]) {
        if (!isValidCoordinate2f(coord)) {
            throw runtime_error("Invalid UV coordinate encountered while parsing " + resPath);
        }
        float x = coord[0];
        float y = coord[1];
        mesh.uvCoordinates.emplace_back(x, y);
    }
}

Vertex parseVertex(const json& vert, const ResourcePath& resPath, Mesh& mesh) {
    if (!vert.is_array() || vert.size() != 3 || !vert[0].is_number_integer() || !vert[1].is_number_integer()
        || !vert[2].is_number_integer()) {
        throw runtime_error("Invalid vertex encountered while parsing " + resPath);
    }
    int position = vert[0] ;
    int uv = vert[1];
    int normal = vert[2];
    if (mesh.positions.size() < position || mesh.normals.size() < normal || mesh.uvCoordinates.size() < uv) {
        throw runtime_error("Mesh resource " + resPath + " has invalid reference");
    }
    return {position - 1, normal - 1, uv - 1};
}

void parseFaces(const json& data, Mesh& mesh, const ResourcePath& resPath) {
    if (!data.contains("faces") || !data["faces"].is_object()) {
        throw runtime_error("No faces element in mesh file " + resPath);
    }
    for (const auto &[key, val]: data["faces"].items()) {
        if (!val.is_array()) {
            throw runtime_error("Invalid UV coordinate encountered while parsing " + resPath);
        }
        mesh.materials.push_back(key);
        vector<Triangle> primitives;
        for (const auto &primitive: val) {
            if (!primitive.is_array() || primitive.size() != 3) {
                throw runtime_error("Invalid primitive definition encountered while parsing mesh " + resPath);
            }
            primitives.emplace_back(parseVertex(primitive[0], resPath, mesh),
                                    parseVertex(primitive[1], resPath, mesh),
                                    parseVertex(primitive[2], resPath, mesh));
        }
        mesh.indices.push_back(primitives);
    }
}

MeshResource MeshResourceResolver::resolveResource(const ResourcePath resPath) {
    ifstream inputFile(resPath);

    if (!inputFile.is_open()) {
        throw invalid_argument("Unable to open mesh resource file " + resPath);
    }

    const json data = json::parse(inputFile);

    auto mesh = make_unique<Mesh>();
    parsePositions(data, *mesh, resPath);
    parseNormals(data, *mesh, resPath);
    parseUVCoordinates(data, *mesh, resPath);
    parseFaces(data, *mesh, resPath);

    inputFile.close();

    return MeshResource (std::move(mesh));
}

void MeshResourceResolver::destroyResource(MeshResource resource) {
}

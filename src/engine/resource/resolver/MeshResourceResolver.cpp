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

void parsePositions(const json &data, Mesh &mesh, const ResourcePath &resPath) {
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

void parseNormals(const json &data, Mesh &mesh, const ResourcePath &resPath) {
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

void parseUVCoordinates(const json &data, Mesh &mesh, const ResourcePath &resPath) {
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

Vertex parseVertex(const json &vert, const ResourcePath &resPath, Mesh &mesh) {
    if (!vert.is_array() || vert.size() != 3 || !vert[0].is_number_integer() || !vert[1].is_number_integer()
        || !vert[2].is_number_integer()) {
        throw runtime_error("Invalid vertex encountered while parsing " + resPath);
    }
    int position = vert[0];
    int uv = vert[1];
    int normal = vert[2];
    if (mesh.positions.size() < position || mesh.normals.size() < normal || mesh.uvCoordinates.size() < uv) {
        throw runtime_error("Mesh resource " + resPath + " has invalid reference");
    }
    return {position - 1, normal - 1, uv - 1};
}

void parsePrimitives(const json &data, Mesh &mesh, const ResourcePath &resPath) {
    if (!data.contains("primitives") || !data["primitives"].is_array()) {
        throw runtime_error("No primitives array in mesh file " + resPath);
    }
    for (const auto &primitive: data["primitives"]) {
        if (!primitive.is_array() || primitive.size() != 3) {
            throw runtime_error("Invalid primitive encountered while parsing " + resPath);
        }
        mesh.primitives.emplace_back(parseVertex(primitive[0], resPath, mesh),
                                     parseVertex(primitive[1], resPath, mesh),
                                     parseVertex(primitive[2], resPath, mesh));
    }
}

float getFloatField(std::string name, const json &obj, const ResourcePath &resPath) {
    if (!obj.contains(name) || !obj[name].is_number_float()) {
        throw runtime_error("Encountered missing or invalid field " + name + " while parsing " + resPath);
    }
    return obj[name];
}

Vector3f getVec3fField(const std::string& name, const json &obj, const ResourcePath &resPath) {
    if (!obj.contains(name) || isValidCoordinate3f(name)) {
        throw runtime_error("Encountered missing or invalid field " + name + " while parsing " + resPath);
    }
    auto coordinate = obj[name];
    return {coordinate[0], coordinate[1], coordinate[2]};
}

void parseBlinnPhongMonochromaticMaterial(const json &material, Mesh &mesh, const ResourcePath &resPath) {
    float ambient = getFloatField("ambient", material, resPath);
    float diffuse = getFloatField("diffuse", material, resPath);
    float shininess = getFloatField("shininess", material, resPath);
    Vector3f specular = getVec3fField("specular", material, resPath);
    Vector3f color = getVec3fField("color", material, resPath);
    mesh.addMaterial<BPMonochromaticMaterial>(ambient, diffuse, specular, shininess, color);
}

void parseBlinnPhongTexturedMaterial(const json &material, Mesh &mesh, const ResourcePath &resPath) {
    // TO-DO
}

void parseMaterials(const json &data, Mesh &mesh, const ResourcePath &resPath) {
    if (!data.contains("materials") || !data["materials"].is_array()) {
        return;
    }
    for (const auto &material: data["materials"]) {
        if (!material.is_object() || !material.contains("type") || !material["type"].is_string()) {
            throw runtime_error("Invalid material encountered while parsing " + resPath);
        }
        std::string type = material["type"];
        if (type == "bp-monochromatic") {
            parseBlinnPhongMonochromaticMaterial(material, mesh, resPath);
        } else if (type == "bp-textured") {
            parseBlinnPhongTexturedMaterial(material, mesh, resPath);
        } else {
            throw runtime_error("Invalid material encountered while parsing " + resPath);
        }
    }
}

void parseGroups(const json &data, Mesh &mesh, const ResourcePath &resPath) {
    if (!data.contains("groups") || !data["groups"].is_object()) {
        return;
    }
    for (const auto &[key, val]: data["groups"].items()) {
        string name = key;
        if (!val.is_array()) {
            throw runtime_error("Invalid group definition encountered while parsing " + resPath);
        }
        vector<int> primitiveRefs;
        for (const auto &primitiveIndex: val) {
            if (!primitiveIndex.is_number_integer()) {
                throw runtime_error("Invalid primitive reference encountered while parsing " + resPath);
            }
            primitiveRefs.push_back(primitiveIndex);
        }
        mesh.groups.emplace_back(primitiveRefs, name);
    }
}

void parseMaterialGroupMappings(const json &data, Mesh &mesh, const ResourcePath &resPath) {
    if (!data.contains("material-mapping") || !data["material-mapping"].is_array()) {
        return;
    }
    for (const auto &mapping: data["material-mapping"]) {
        if (!mapping.is_array()) {
            throw runtime_error("Invalid material-group mapping definition encountered while parsing " + resPath);
        }
        vector<string> groups;
        for (const auto &group: mapping) {
            if (!group.is_string()) {
                throw runtime_error("Invalid material-group mapping definition encountered while parsing " + resPath);
            }
            groups.push_back(group);
        }
        mesh.materialMappings.emplace_back(groups);
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
    parsePrimitives(data, *mesh, resPath);
    parseMaterials(data, *mesh, resPath);
    parseGroups(data, *mesh, resPath);
    parseMaterialGroupMappings(data, *mesh, resPath);

    inputFile.close();

    return MeshResource(std::move(mesh));
}

void MeshResourceResolver::destroyResource(MeshResource resource) {
}

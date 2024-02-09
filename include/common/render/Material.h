#ifndef TRUCKER_GAME_MATERIAL_H
#define TRUCKER_GAME_MATERIAL_H

struct Material {
    virtual std::string getTypeString();
};

struct BPMonochromaticMaterial: public Material {
    float ambient;
    float diffuse;
    Vector3f specular;
    float shininess;
    Vector3f color;

    std::string getTypeString() override {
        return "bp-monochromatic";
    }

    BPMonochromaticMaterial(float ambient, float diffuse, const Vector3f &specular, float shininess,
                            const Vector3f &color) : ambient(ambient), diffuse(diffuse), specular(specular),
                                                     shininess(shininess), color(color) {}
};

#endif //TRUCKER_GAME_MATERIAL_H

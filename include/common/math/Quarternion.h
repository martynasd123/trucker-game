#ifndef TRUCKER_GAME_QUARTERNION_H
#define TRUCKER_GAME_QUARTERNION_H

class Quaternion {
    float x, y, z, w;
public:
    static const Quaternion IDENTITY;
public:
    Quaternion(float x, float y, float z, float w);
};

#endif //TRUCKER_GAME_QUARTERNION_H

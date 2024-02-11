#ifndef TRUCKER_GAME_FRAGMENTSHADER_H
#define TRUCKER_GAME_FRAGMENTSHADER_H

#include "Shader.h"

class FragmentShader: public Shader {
public:
    explicit FragmentShader(const string& code);
};


#endif //TRUCKER_GAME_FRAGMENTSHADER_H

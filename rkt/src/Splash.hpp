#ifndef Splash_hpp
#define Splash_hpp

#include <stdio.h>
#include <iostream>
#include <queue>
#include "Definitions.h"
#include "Scene.hpp"
#include "Animation.hpp"
#include "ShaderProgram.hpp"

class Splash : Scene {
    GLuint dissolveRampTextureId;
    GLuint dissolveNoiseTextureId;
    GLuint splashLogo;

    float dissolve = 0;
    
    ShaderProgram *dissolveProgram;

    std::queue<Animation*> animationQueue;
    
    ~Splash();
public:
    Splash(Renderer *r, RocketteServiceImpl *service);
    void render();
    void renderFixed();
    bool update(float delta);
};

#endif /* Splash_hpp */

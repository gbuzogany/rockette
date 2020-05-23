#ifndef Scene_hpp
#define Scene_hpp

#include <stdio.h>
#include "Renderer.hpp"
#include "RocketteService.hpp"

class Scene {
protected:
    Renderer *_r;
    RocketteServiceImpl *_service;
    
public:
    Scene(Renderer *renderer, RocketteServiceImpl *service);
    virtual void render() = 0;
    virtual void renderFixed() = 0;
    virtual bool update(float delta) = 0;
};

#endif /* Scene_hpp */

#ifndef Sprite_hpp
#define Sprite_hpp

#include <stdio.h>
#include <iostream>
#include <string>

class Sprite {
public:
    float x, y;
    float width, height;
    std::string name;
    
    Sprite(std::string name, int x, int y, int width, int height);
    ~Sprite();
};

#endif /* Sprite_hpp */

#ifndef Animation_hpp
#define Animation_hpp

#include <stdio.h>
#include <string>

class Animation {
    float duration, elapsed = 0, from, to;
    std::string id;
    
public:
    Animation(std::string id, float from, float to, float duration);
    float animate(float delta);
    bool complete();
    std::string getId();
};

#endif /* Animation_hpp */

#ifndef Utils_hpp
#define Utils_hpp

#include <stdio.h>
#include <sys/types.h>
#include <utility>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

enum {LEFT, CENTER, RIGHT, TOP, BOTTOM};

class Utils {
    
public:
    static float map(float value, float inMin, float inMax, float outMin, float outMax);
    static std::pair<float, float> calculateTextCenter(float totalWidth, uint hAlign, uint vAlign, int fontSize);
};

#endif /* Utils_hpp */

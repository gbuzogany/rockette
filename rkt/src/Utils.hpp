#ifndef Utils_hpp
#define Utils_hpp

#include <stdio.h>
#include <sys/types.h>
#include <utility>
#include <algorithm>
#include <cctype>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>

using namespace glm;

enum {LEFT, CENTER, RIGHT, TOP, BOTTOM};

class Utils {
    
public:
    static float map(float value, float inMin, float inMax, float outMin, float outMax);
    static std::pair<float, float> calculateTextCenter(float totalWidth, uint hAlign, uint vAlign, int fontSize);
    static std::string toLower(std::string input);
    static GLenum getTextureConstFromIndex(int index);
};

#endif /* Utils_hpp */

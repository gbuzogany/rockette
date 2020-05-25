#include "Utils.hpp"


float Utils::map(float value, float inMin, float inMax, float outMin, float outMax) {
    return outMin + (outMax - outMin) * (value - inMin) / (inMax - inMin);
}

std::pair<float, float> Utils::calculateTextCenter(float totalWidth, uint hAlign, uint vAlign, int fontSize) {
    
    std::pair<float, float> centerPoint(0, 0);
    
    switch(hAlign) {
        case CENTER: {
            centerPoint.first = -totalWidth/2;
            break;
        }
        case RIGHT: {
            centerPoint.first = -totalWidth;
            break;
        }
    }
    
    switch(vAlign) {
        case CENTER: {
            centerPoint.second = -fontSize/2.8;
            break;
        }
        case TOP: {
            centerPoint.second = -fontSize;
            break;
        }
    }
    
    return centerPoint;
}


std::string Utils::toLower(std::string input) {
    std::transform(input.begin(), input.end(), input.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    return input;
}

GLenum Utils::getTextureConstFromIndex(int index) {
    switch (index) {
        case 0:
            return GL_TEXTURE0;
            break;
        case 1:
            return GL_TEXTURE1;
            break;
        case 2:
            return GL_TEXTURE2;
            break;
        case 3:
            return GL_TEXTURE3;
            break;
        case 4:
            return GL_TEXTURE4;
            break;
        default:
            break;
    }
    return -1;
}

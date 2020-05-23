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

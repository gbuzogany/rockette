#include <iostream>
#include <map>
#include <math.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include "FontWrapper.hpp"
#include "Renderer.hpp"

std::map<std::string, FT_Face> FontWrapper::faceMap;

FontWrapper::FontWrapper(std::string fontName, int size, std::vector<FT_ULong> charList) {
    FT_Face face;
    
    int error = FontWrapper::getFace(fontName, face);
    if (!error) {
        face = FontWrapper::faceMap[fontName];
    }
    else {
        printf("Error: Attempting to load a FontFace that isn't loaded.");
        throw 1;
    }
    
    createFontTextureAtlas(face, size, charList);
}

FontWrapper::~FontWrapper() {
    glDeleteTextures(1, &texture);
}

int FontWrapper::createFontTextureAtlas(FT_Face &face, int size, std::vector<FT_ULong> charList) {
    FT_Set_Pixel_Sizes(face, 0, size);
    fontSize = size;
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction
    
    for (auto it = charList.begin(); it != charList.end(); it++) {
        FT_ULong character = *it;
        loadCharProperties(face, size, character);
    }
    
    int numChars = ceil(sqrt(charList.size()));
    
    int texWidth = closestPowerOf2(numChars * maxWidth);
    int texHeight = closestPowerOf2(numChars * maxHeight);
    
    if (texWidth > texHeight) {
        texSize = texWidth;
    }
    else {
        texSize = texHeight;
    }
    
    printf("Font texture atlas size: %d, %d -> %f x %f\n", maxWidth, maxHeight, texSize, texSize);
    
    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, texSize, texSize, 0, GL_ALPHA, GL_UNSIGNED_BYTE, 0);
    
    int x = 0;
    int y = 0;
    
    for (auto it = charList.begin(); it != charList.end(); it++) {
        FT_ULong character = *it;
        characters[character].texCoords = glm::ivec2(x, y);
        addCharFromCharCode(face, size, character, x, y);
        x += maxWidth;
        if (x + maxWidth >= texWidth) {
            x = 1;
            y += maxHeight;
        }
        if (y > texHeight) {
            printf("Error: Font doesn't fit in texture.");
        }
    }
    
    return 0;
}

void FontWrapper::addCharFromCharCode(FT_Face &face, int size, FT_ULong charCode, int x, int y) {
    FT_GlyphSlot glyph = face->glyph;
    
    // Load character glyph
    if (FT_Load_Char(face, charCode, FT_LOAD_RENDER | FT_LOAD_NO_HINTING))
    {
        std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
        return;
    }
    
    glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, glyph->bitmap.width, glyph->bitmap.rows, GL_ALPHA, GL_UNSIGNED_BYTE, glyph->bitmap.buffer);
}

int FontWrapper::closestPowerOf2(int n) {
    n--;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    n++;
    return n;
}

void FontWrapper::loadCharProperties(FT_Face &face, int size, FT_ULong charCode) {
    if (FT_Load_Char(face, charCode, FT_LOAD_RENDER | FT_LOAD_NO_HINTING))
    {
        std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
        return;
    }
    
    if (face->glyph->bitmap.width > maxWidth) {
        maxWidth = face->glyph->bitmap.width + 1;
    }
    if (face->glyph->bitmap.rows > maxHeight) {
        maxHeight = face->glyph->bitmap.rows + 1;
    }
    
    Character character = {
        glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
        glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
        (GLuint) face->glyph->advance.x,
        glm::ivec2(0, 0)
    };
    characters.insert(std::pair<GLchar, Character>(charCode, character));
}

int FontWrapper::getFontSize() {
    return fontSize;
}

int FontWrapper::getCharacter(GLchar key, Character &out) {
    if (characters.find(key) != characters.end()) {
        out = characters[key];
        return 0;
    }
    return -1;
}

#pragma STATIC

int FontWrapper::loadFontFace(Renderer* r, std::string name, std::string path) {
    FT_Face face;
    int loaded = FontWrapper::getFace(name, face);
    if (loaded == -1) {
        if (FT_New_Face(r->ft, path.c_str(), 0, &face)) {
            std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
            return -2;
        }
        faceMap[name] = face;
        return 0;
    }
    else {
        std::cout << "FontFace \"" << name << "\" was already loaded." << std::endl;
    }
    return -1;
}

int FontWrapper::getFace(std::string name, FT_Face &face) {
    if (faceMap.find(name) != faceMap.end()) {
        face = faceMap[name];
        return 0;
    }
    return -1;
}

#ifndef Font_hpp
#define Font_hpp

#include <stdio.h>
#include <vector>
#include <glad/glad.h>

struct Character {
    glm::ivec2 size;       // Size of glyph
    glm::ivec2 bearing;    // Offset from baseline to left/top of glyph
    GLuint     advance;    // Offset to advance to next glyph
    glm::ivec2 texCoords;
};

class Renderer;

class FontWrapper {
    int createFontTextureAtlas(FT_Face &face, int size, std::vector<FT_ULong> charList);
    void addCharFromCharCode(FT_Face &face, int size, FT_ULong charCode, int x, int y);
    void loadCharProperties(FT_Face &face, int size, FT_ULong charCode);
    int closestPowerOf2(int n);
    
    std::map<GLchar, Character> characters;
    
    static std::map<std::string, FT_Face> faceMap;
    
    int maxWidth = 0;
    int maxHeight = 0;
    int fontSize;
    
public:
    float texSize;
    GLuint texture;
    
    int getFontSize();
    int getCharacter(GLchar key, Character &out);
    
    FontWrapper(std::string fontName, int size, std::vector<FT_ULong> charList);
    ~FontWrapper();
    
    static int loadFontFace(Renderer* r, std::string name, std::string path);
    static int getFace(std::string name, FT_Face &face);
};

#endif /* Font_hpp */

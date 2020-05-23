#ifndef Renderer_hpp
#define Renderer_hpp

#define _USE_MATH_DEFINES
#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <stdio.h>
#include <string>
#include <map>
#include <glad/glad.h>
#include <SDL.h>
#define GL_GLEXT_PROTOTYPES 1
#include <SDL_opengles2.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "ShaderProgram.hpp"
#include "FontWrapper.hpp"
#include "Texture.hpp"
#include "Utils.hpp"

class Renderer {
private:
    SDL_GLContext context;
    GLuint vertexbuffer;
    GLuint VAO, VBO;
    
    GLuint lastTexture = -1;
    GLuint lastProgram = -1;
    
    Uint32 startTime = 0;
    Uint32 endTime = 0;
    float time = 0;
    Uint32 delta = 0;
    float fps = 60.0;
    Uint32 timePerFrame = 16; // miliseconds
    
    GLfloat globalAlpha = 0.0;
public:
    FT_Library ft;
    
    ShaderProgram *textProgram;
    ShaderProgram *defaultTextProgram;
    ShaderProgram *defaultTextureProgram;
    
    SDL_Window *window;
    
    Renderer();
    ~Renderer();
    
    void initGraphics();
    void initShaders();
    void updateScreen();
    
    float startFrame();
    void endFrame();
    short getFrameRate();
    
    GLuint getVertexBuffer();

    float renderText(FontWrapper &font, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color, uint hAlign = LEFT, uint vAlign = BOTTOM);
    void renderTexture(GLuint textureId, GLfloat x, GLfloat y, GLfloat width, GLfloat height, ShaderProgram *program = nullptr);
    void renderRect(GLfloat x, GLfloat y, GLfloat width, GLfloat height, bool flipY = false);
    
    void bindTexture(GLuint texId);
    void setTextProgram(ShaderProgram *program);
    void useProgram(ShaderProgram &program);
    
    void drawCircle(GLfloat x, GLfloat y, GLfloat radius, GLint numberOfSides);
    void renderFlat(ShaderProgram &program, GLfloat x, GLfloat y, GLfloat width, GLfloat height, bool flipY = false);
    void setProgramGlobalAlpha(ShaderProgram &program);
    void setGlobalAlpha(float alpha);
    
    void createFramebuffer(GLuint &frameBuffer, GLuint &screenTexture, GLuint width, GLuint height);
    void bindFramebuffer(GLuint frameBuffer);
    void clear();
};

#endif /* Renderer_hpp */

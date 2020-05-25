#ifndef Renderer_hpp
#define Renderer_hpp

#define _USE_MATH_DEFINES
#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <stdio.h>
#include <assert.h>
#include <iostream>
#include <string>
#include <map>
#include <glad/glad.h>
#include <SDL.h>
#define GL_GLEXT_PROTOTYPES 1
#include <SDL_opengles2.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "RawShaderProgram.hpp"
#include "FontWrapper.hpp"
#include "Texture.hpp"
#include "Utils.hpp"
#include "Definitions.h"

class Renderer {
private:
    SDL_GLContext context;
    GLuint vertexbuffer;
    GLuint uvbuffer;
    GLuint VAO, VBO;
    
    GLuint lastTexture = -1;
    GLuint lastProgram = -1;
    
    Uint32 startTime = 0;
    Uint32 endTime = 0;
    float time = 0;
    float totalTime = 0;
    Uint32 delta = 0;
    float fps = 60.0;
    Uint32 timePerFrame = 16; // miliseconds
    
    GLfloat globalAlpha = 0.0;
public:
    FT_Library ft;
    
    RawShaderProgram *hBlurProgram;
    RawShaderProgram *vBlurProgram;
    
    GLuint screenTexture1;
    GLuint frameBuffer1;
    GLuint screenTexture2;
    GLuint frameBuffer2;
    
    RawShaderProgram *textProgram;
    RawShaderProgram *defaultTextProgram;
    RawShaderProgram *defaultTextureProgram;
    
    SDL_Window *window;
    
    Renderer();
    ~Renderer();
    
    void initGraphics();
    void initShaders();
    void updateScreen();
    
    float startFrame();
    void endFrame();
    short getFrameRate();
    
    float getTotalTime();
    
    GLuint blurTexture(GLuint texId, float blurAmount);
    
    GLuint getVertexBuffer();
    GLuint getUVBuffer();

    float renderText(FontWrapper &font, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color, uint hAlign = LEFT, uint vAlign = BOTTOM);
    void renderTexture(GLuint textureId, GLfloat x, GLfloat y, GLfloat width, GLfloat height, bool flipY = false, bool defaultProgram = true);
    void renderRect(GLfloat x, GLfloat y, GLfloat width, GLfloat height, bool flipY = false);
    
    void bindTexture(GLuint texId);
    void setTextProgram(RawShaderProgram *program);
    void useProgram(RawShaderProgram &program);
    
    void drawCircle(GLfloat x, GLfloat y, GLfloat radius, GLint numberOfSides);
    void renderFlat(RawShaderProgram &program, GLfloat x, GLfloat y, GLfloat width, GLfloat height, bool flipY = false);
    void setProgramGlobalAlpha(RawShaderProgram &program);
    void setGlobalAlpha();
    void setGlobalAlpha(float alpha);
    
    void createFramebuffer(GLuint &frameBuffer, GLuint &screenTexture, GLuint width, GLuint height);
    void bindFramebuffer(GLuint frameBuffer);
    void clear();
};

#endif /* Renderer_hpp */

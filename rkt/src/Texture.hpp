#ifndef Texture_hpp
#define Texture_hpp

#include <stdio.h>
#include <glad/glad.h>
#include <SDL.h>
#define GL_GLEXT_PROTOTYPES 1
#include <SDL_opengles2.h>

class Texture {
public:
    static GLuint loadTGA(const char * imagepath);
    static void destroyTexture(GLuint textureId);
};

#endif /* Texture_hpp */

#include "Texture.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

GLuint Texture::loadTGA(const char * imagepath) {
    
    int width, height, channels;
    unsigned char *image = stbi_load(imagepath, &width, &height, &channels, STBI_rgb_alpha);
    if (image == NULL) {
        printf("Could not be open file: %s.\n", imagepath);
        return 0;
    }
    
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    free(image);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);
    
    return textureID;
}

void Texture::destroyTexture(GLuint textureId) {
    glDeleteTextures(1, &textureId);
}

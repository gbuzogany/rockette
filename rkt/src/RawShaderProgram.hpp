#ifndef RawShaderProgram_hpp
#define RawShaderProgram_hpp

#include <stdio.h>
#include <assert.h>
#include <string>
#include <map>
#include <glad/glad.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>

#ifdef Status
#undef Status
#endif

class RawShaderProgram {
    GLuint Id, vs, fs;
    std::map<std::string, GLuint> uniformLocations;
    
public:
    
    RawShaderProgram(const std::string vertexShader, const std::string fragmentShader);
    ~RawShaderProgram();
    
    GLuint compileShader(std::string filename, GLuint shaderType);
    GLuint getUniformLocation(std::string name);
    GLuint getId() { return Id; }
};

#endif /* ShaderProgram_hpp */

#include "ShaderProgram.hpp"
#include <iostream>

ShaderProgram::ShaderProgram(const std::string vertexShader, const std::string fragmentShader) {
    vs = compileShader(vertexShader, GL_VERTEX_SHADER);
    fs = compileShader(fragmentShader, GL_FRAGMENT_SHADER);
    
    Id = glCreateProgram();
    glAttachShader(Id, vs);
    glAttachShader(Id, fs);
    glLinkProgram(Id);
    assert(glGetError() == GL_NO_ERROR);
    glUseProgram(Id);
    assert(glGetError() == GL_NO_ERROR);
}

GLuint ShaderProgram::getUniformLocation(std::string name) {
    if (uniformLocations.find(name) == uniformLocations.end()) {
        GLuint uniform = glGetUniformLocation(Id, name.c_str());
        uniformLocations[name] = uniform;
        return uniform;
    }
    return uniformLocations[name];
}

ShaderProgram::~ShaderProgram() {
    glDeleteShader(Id);
}

GLuint ShaderProgram::compileShader(const std::string filename, const GLuint shaderSype) {
    GLchar* Src;
    GLuint progId;
    
    printf("Loading %s...\n", filename.c_str());
    FILE* f = fopen(filename.c_str(), "rb");
    assert(f);
    fseek(f,0,SEEK_END);
    long sz = ftell(f);
    fseek(f,0,SEEK_SET);
    Src = new GLchar[sz+1];
    fread(Src,1,sz,f);
    Src[sz] = 0;
    fclose(f);
    
    progId = glCreateShader(shaderSype);
    glShaderSource(progId, 1, (const GLchar**)&Src, 0);
    glCompileShader(progId);
    assert(glGetError() == GL_NO_ERROR);
    
    delete[] Src;
    
    return progId;
}

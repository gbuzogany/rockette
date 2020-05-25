#include "RawShaderProgram.hpp"
#include <iostream>

RawShaderProgram::RawShaderProgram(const std::string vertexShader, const std::string fragmentShader) {
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

GLuint RawShaderProgram::getUniformLocation(std::string name) {
    if (uniformLocations.find(name) == uniformLocations.end()) {
        GLuint uniform = glGetUniformLocation(Id, name.c_str());
        if (uniform == -1) {
//            std::cout << "RawShaderProgram: Uniform \"" << name << "\" not found." << std::endl;
            return -1;
        }
        uniformLocations[name] = uniform;
        return uniform;
    }
    return uniformLocations[name];
}

RawShaderProgram::~RawShaderProgram() {
    glDeleteShader(Id);
}

GLuint RawShaderProgram::compileShader(const std::string filename, const GLuint shaderSype) {
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

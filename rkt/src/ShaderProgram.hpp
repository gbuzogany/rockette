//
//  ShaderProgram.hpp
//  dash
//
//  Created by Gustavo Buzogany Eboli on 24/05/2020.
//  Copyright © 2020 gbuzogany.com. All rights reserved.
//

#ifndef ShaderProgram_hpp
#define ShaderProgram_hpp

#include <stdio.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "RawShaderProgram.hpp"
#include "rapidjson/reader.h"
#include "rapidjson/error/en.h"
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include "Utils.hpp"
#include "Renderer.hpp"

using namespace rapidjson;

class ShaderProgram {
    RawShaderProgram *rawShaderProgram;
    
    std::map<std::string, GLuint> textureValuesMap;
    std::map<std::string, GLuint> uintValuesMap;
    std::map<std::string, GLfloat> floatValuesMap;
    std::map<std::string, glm::vec3> vec3ValuesMap;
    std::map<std::string, glm::vec4> vec4ValuesMap;
    std::map<std::string, glm::mat4> mat4ValuesMap;
    
public:
    ShaderProgram(std::string vertexShaderPath, std::string fragmentShaderPath, std::string uniformsPath);
    ~ShaderProgram();
    
    void parseUniforms(std::string uniformsPath);
    void parseElement(std::string name, const GenericObject<true, GenericValue<UTF8<>, MemoryPoolAllocator<>>> &obj);
    void parseFloat(std::string name, const GenericObject<true, GenericValue<UTF8<>, MemoryPoolAllocator<>>> &obj);
    void parseTexture(std::string name, const GenericObject<true, GenericValue<UTF8<>, MemoryPoolAllocator<>>> &obj);
    void parseVec3(std::string name, const GenericObject<true, GenericValue<UTF8<>, MemoryPoolAllocator<>>> &obj);
    void parseVec4(std::string name, const GenericObject<true, GenericValue<UTF8<>, MemoryPoolAllocator<>>> &obj);
    
    GLuint getUniform(std::string uniformName);
    
    void setTextureUniform(std::string name, GLuint value);
    void setUIntUniform(std::string name, GLuint value);
    void setFloatUniform(std::string name, GLfloat value);
    void setVec3Uniform(std::string name, glm::vec3 value);
    void setVec4Uniform(std::string name, glm::vec4 value);
    void setMat4Uniform(std::string name, glm::mat4 value);
    
    void use(Renderer *renderer);
};

#endif /* ShaderProgram_hpp */

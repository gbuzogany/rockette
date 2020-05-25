//
//  ShaderProgram.cpp
//  dash
//
//  Created by Gustavo Buzogany Eboli on 24/05/2020.
//  Copyright © 2020 gbuzogany.com. All rights reserved.
//

#include "ShaderProgram.hpp"

ShaderProgram::ShaderProgram(std::string vertexShaderPath, std::string fragmentShaderPath, std::string uniformsPath) {
    rawShaderProgram = new RawShaderProgram(vertexShaderPath, fragmentShaderPath);
    parseUniforms(uniformsPath);
}

ShaderProgram::~ShaderProgram() {
    delete rawShaderProgram;
}

GLuint ShaderProgram::getUniform(std::string uniformName) {
    return rawShaderProgram->getUniformLocation(uniformName);
}

void ShaderProgram::parseUniforms(std::string uniformsPath) {
    
    FILE *config = fopen(uniformsPath.c_str(), "r");
    Document document;
    
    char buffer[65535];
    FileReadStream is(config, buffer, sizeof(buffer));
    
    document.ParseStream<0, UTF8<>, FileReadStream>(is);
    
    if(document.IsObject()) {
        for (Value::ConstMemberIterator itr = document.MemberBegin(); itr != document.MemberEnd(); ++itr) {
            parseElement(itr->name.GetString(), itr->value.GetObject());
        }
    }
    
    fclose(config);
}

void ShaderProgram::parseElement(std::string name, const GenericObject<true, GenericValue<UTF8<>, MemoryPoolAllocator<>>> &obj) {
    
    if (obj.HasMember("type")) {
        if(obj["type"].IsString()) {
            std::string value = obj["type"].GetString();
            if (Utils::toLower(value).compare("group") == 0) {
                // group
                for (Value::ConstMemberIterator itr = obj.MemberBegin(); itr != obj.MemberEnd(); ++itr) {
                    if (itr->value.IsObject()) {
                        parseElement(itr->name.GetString(), itr->value.GetObject());
                    }
                }
            }
            else if (Utils::toLower(value).compare("t") == 0) {
                // texture
                parseTexture(name, obj);
            }
            else if (Utils::toLower(value).compare("vec3") == 0) {
                parseVec3(name, obj);
            }
            else if (Utils::toLower(value).compare("vec4") == 0) {
                parseVec4(name, obj);
            }
        }
    }
    else {
        // float
        parseFloat(name, obj);
    }
}

void ShaderProgram::parseTexture(std::string name, const GenericObject<true, GenericValue<UTF8<>, MemoryPoolAllocator<>>> &obj) {
}


void ShaderProgram::parseFloat(std::string name, const GenericObject<true, GenericValue<UTF8<>, MemoryPoolAllocator<>>> &obj) {
    float value = 0;
    if (obj.HasMember("value")) {
        if(obj["value"].IsNumber()) {
            value = obj["value"].GetFloat();
        }
    }
    floatValuesMap[name] = value;
}

void ShaderProgram::parseVec3(std::string name, const GenericObject<true, GenericValue<UTF8<>, MemoryPoolAllocator<>>> &obj) {
    glm::vec3 value(0);
    if (obj.HasMember("value")) {
        if(obj["value"].IsArray() && obj["value"].Size() == 3) {
            value.x = obj["value"][0].GetFloat();
            value.y = obj["value"][1].GetFloat();
            value.z = obj["value"][2].GetFloat();
        }
    }
    vec3ValuesMap[name] = value;
}

void ShaderProgram::parseVec4(std::string name, const GenericObject<true, GenericValue<UTF8<>, MemoryPoolAllocator<>>> &obj) {
    glm::vec4 value(0);
    if (obj.HasMember("value")) {
        if(obj["value"].IsArray() && obj["value"].Size() == 4) {
            value.x = obj["value"][0].GetFloat();
            value.y = obj["value"][1].GetFloat();
            value.z = obj["value"][2].GetFloat();
            value.w = obj["value"][3].GetFloat();
        }
    }
    vec4ValuesMap[name] = value;
}

void ShaderProgram::setTextureUniform(std::string name, GLuint value) {
    textureValuesMap[name] = value;
}

void ShaderProgram::setUIntUniform(std::string name, GLuint value) {
    uintValuesMap[name] = value;
}

void ShaderProgram::setFloatUniform(std::string name, GLfloat value) {
    floatValuesMap[name] = value;
}

void ShaderProgram::setVec3Uniform(std::string name, glm::vec3 value) {
    vec3ValuesMap[name] = value;
}

void ShaderProgram::setVec4Uniform(std::string name, glm::vec4 value) {
    vec4ValuesMap[name] = value;
}

void ShaderProgram::setMat4Uniform(std::string name, glm::mat4 value) {
    mat4ValuesMap[name] = value;
}

void ShaderProgram::use(Renderer *r) {
    r->useProgram(*rawShaderProgram);

    int currTexIndex = 0;
    
    for (auto it = textureValuesMap.begin(); it != textureValuesMap.end(); ++it) {
        std::string name = it->first;
        GLuint uniform_id = rawShaderProgram->getUniformLocation(name);
        if (uniform_id != -1) {
            GLenum texIndex = Utils::getTextureConstFromIndex(currTexIndex);
            glActiveTexture(texIndex);
            r->bindTexture(it->second);
            glUniform1i(uniform_id, currTexIndex++);
        }
    }
    
    for (auto it = uintValuesMap.begin(); it != uintValuesMap.end(); ++it) {
        std::string name = it->first;
        GLuint uniform_id = rawShaderProgram->getUniformLocation(name);
        if (uniform_id != -1) {
            glUniform1i(uniform_id, it->second);
        }
    }
    
    for (auto it = floatValuesMap.begin(); it != floatValuesMap.end(); ++it) {
        std::string name = it->first;
        GLuint uniform_id = rawShaderProgram->getUniformLocation(name);
        if (uniform_id != -1) {
            glUniform1f(uniform_id, it->second);
        }
    }
    
    for (auto it = vec3ValuesMap.begin(); it != vec3ValuesMap.end(); ++it) {
        std::string name = it->first;
        GLuint uniform_id = rawShaderProgram->getUniformLocation(name);
        if (uniform_id != -1) {
            glm::vec3 value = it->second;
            glUniform3f(uniform_id, value.x, value.y, value.z);
        }
    }
    
    for (auto it = vec4ValuesMap.begin(); it != vec4ValuesMap.end(); ++it) {
        std::string name = it->first;
        GLuint uniform_id = rawShaderProgram->getUniformLocation(name);
        if (uniform_id != -1) {
            glm::vec4 value = it->second;
            glUniform4f(uniform_id, value.x, value.y, value.z, value.w);
        }
    }
    
    for (auto it = mat4ValuesMap.begin(); it != mat4ValuesMap.end(); ++it) {
        std::string name = it->first;
        GLuint uniform_id = rawShaderProgram->getUniformLocation(name);
        if (uniform_id != -1) {
            glm::mat4 value = it->second;
            glUniformMatrix4fv(uniform_id, 1, GL_FALSE, &value[0][0]);
        }
    }
}

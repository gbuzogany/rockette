#include <stdio.h>
#include <string>
#include <iostream>

#include "SpriteMap.hpp"

SpriteMap::SpriteMap(std::string jsonPath) {
    loadSprites(jsonPath);
}

SpriteMap::~SpriteMap() {
    for (auto it = spriteMap.begin(); it != spriteMap.end(); ++it) {
        delete it->second;
    }
}

void SpriteMap::loadSprites(std::string jsonPath) {
    
    FILE *config = fopen(jsonPath.c_str(), "r");
    Document document;
    
    char buffer[65535];
    FileReadStream is(config, buffer, sizeof(buffer));
    
    document.ParseStream<0, UTF8<>, FileReadStream>(is);
    
    if(document.IsObject()) {
        for (Value::ConstMemberIterator itr = document.MemberBegin(); itr != document.MemberEnd(); ++itr) {
            std::string name(itr->name.GetString());
            if (name.compare("texture") == 0) {
                parseTexture(itr->value.GetObject());
            }
            if (name.compare("sprites") == 0) {
                parseIcons(itr->value.GetObject());
            }
        }
    }
}

void SpriteMap::parseTexture(const GenericObject<true, GenericValue<UTF8<>, MemoryPoolAllocator<>>> obj) {
    for (Value::ConstMemberIterator itr = obj.MemberBegin(); itr != obj.MemberEnd(); ++itr) {
        std::string name(itr->name.GetString());
        
        if (name.compare("path") == 0) {
            iconsTexture = Texture::loadTGA(itr->value.GetString());
        }
        if (name.compare("width") == 0) {
            texWidth = itr->value.GetInt();
        }
        if (name.compare("height") == 0) {
            texHeight = itr->value.GetInt();
        }
    }
}

void SpriteMap::parseIcons(const GenericObject<true, GenericValue<UTF8<>, MemoryPoolAllocator<>>> obj) {
    for (Value::ConstMemberIterator itr = obj.MemberBegin(); itr != obj.MemberEnd(); ++itr) {
        std::string name(itr->name.GetString());
        
        int x = 0;
        int y = 0;
        int width = 0;
        int height = 0;
        
        auto obj = itr->value.GetObject();
        for (Value::ConstMemberIterator pitr = obj.MemberBegin(); pitr != obj.MemberEnd(); ++pitr) {
            std::string name(pitr->name.GetString());
            
            if (name.compare("x") == 0) {
                x = pitr->value.GetInt();
            }
            if (name.compare("y") == 0) {
                y = pitr->value.GetInt();
            }
            if (name.compare("width") == 0) {
                width = pitr->value.GetInt();
            }
            if (name.compare("height") == 0) {
                height = pitr->value.GetInt();
            }
        }
        Sprite *sprite = new Sprite(name, x, y, width, height);
        spriteMap[name] = sprite;
    }
}

void SpriteMap::renderIcon(Renderer *r, std::string name, int x, int y, float scale, glm::vec3 color) {
    r->useProgram(*r->defaultTextProgram);
    
    if (spriteMap.find(name) == spriteMap.end()) {
        std::cout << "Icon " << name << " not found." << std::endl;
        return;
    }
    
    Sprite *icon = spriteMap[name];
    
    GLuint u_textureId = r->defaultTextProgram->getUniformLocation("tex");
    GLuint u_projectionID = r->defaultTextProgram->getUniformLocation("projection");
    GLuint u_color = r->defaultTextProgram->getUniformLocation("textColor");
    
    glm::mat4 projection = glm::ortho(0.0f, WIDTH, 0.0f, HEIGHT);
    glUniformMatrix4fv(u_projectionID, 1, GL_FALSE, &projection[0][0]);
    
    glUniform1i(u_textureId, 0);
    glUniform3f(u_color, color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);
    
    r->bindTexture(iconsTexture);
    
    GLfloat xpos = x;
    GLfloat ypos = HEIGHT - y - (icon->height) * scale;
    
    GLfloat iconPx = icon->x / texWidth;
    GLfloat iconPy = (icon->y) / texHeight;
    GLfloat iconHeight = icon->height / texHeight;
    GLfloat iconWidth = icon->width / texWidth;
    
    // 0 1
    // 3 2
    
    GLfloat vertices[6][4] = {
        { xpos,               ypos + (icon->height) * scale,   iconPx, iconPy }, // 0
        { xpos,               ypos,                  iconPx, iconPy + iconHeight }, // 3
        { xpos + (icon->width) * scale, ypos,                  iconPx + iconWidth, iconPy + iconHeight }, // 2
        
        { xpos,               ypos + (icon->height) * scale,   iconPx, iconPy },    // 0
        { xpos + (icon->width) * scale, ypos,                  iconPx + iconWidth, iconPy + iconHeight}, // 2
        { xpos + (icon->width) * scale, ypos + (icon->height) * scale,   iconPx + iconWidth, iconPy }     // 1
    };

//    bool flipY = false;
//    float top = flipY ? 0.0 : 1.0;
//    float bottom = flipY ? 1.0 : 0.0;
//
//    GLfloat vertices[6][4] = {
//        { xpos,               ypos + icon->height,   0.0, top }, // 0
//        { xpos,               ypos,                  0.0, bottom }, // 3
//        { xpos + icon->width, ypos,                  1.0, bottom }, // 2
//
//        { xpos,               ypos + icon->height,   0.0, top },    // 0
//        { xpos + icon->width, ypos,                  1.0, bottom }, // 2
//        { xpos + icon->width, ypos + icon->height,   1.0, top }     // 1
//    };
    
    GLuint vertexbuffer = r->getVertexBuffer();
    
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, &vertices[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

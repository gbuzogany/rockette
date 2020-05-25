#include "Renderer.hpp"

Renderer::Renderer()
{
    if (FT_Init_FreeType(&ft)) {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
    }
}

void Renderer::initShaders() {
    defaultTextProgram = new RawShaderProgram( "rkt/etc/shaders/TextVertex.glsl", "rkt/etc/shaders/TextFragment.glsl" );
    defaultTextureProgram = new RawShaderProgram( "rkt/etc/shaders/TextureVertexShader.glsl", "rkt/etc/shaders/TextureFragmentShader.glsl" );
    
    hBlurProgram = new RawShaderProgram( "rkt/etc/shaders/HBlurVertexShader.glsl", "rkt/etc/shaders/BlurFragmentShader.glsl" );
    vBlurProgram = new RawShaderProgram( "rkt/etc/shaders/VBlurVertexShader.glsl", "rkt/etc/shaders/BlurFragmentShader.glsl" );
    
    textProgram = defaultTextProgram;
    
    createFramebuffer(frameBuffer1, screenTexture1, WIDTH, HEIGHT);
    createFramebuffer(frameBuffer2, screenTexture2, WIDTH, HEIGHT);
}

void Renderer::initGraphics()
{
    assert(SDL_Init(SDL_INIT_VIDEO) == 0);
    
#if defined(_WIN32) || defined(__MACOSX__)
    SDL_SetHint(SDL_HINT_OPENGL_ES_DRIVER, "1"); // Force SDL to use ANGLE for it's OpenGLES2 implementation
#endif
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_EGL, 1);
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    
    window = SDL_CreateWindow("Rockette", 100, 100, 800, 480, SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN);
    assert(window);

    context = SDL_GL_CreateContext(window);
    assert(context);
    
    int version = gladLoadGLES2Loader((GLADloadproc) SDL_GL_GetProcAddress);
    if(!version) {
        printf("Something went wrong!\n");
        exit(-1);
    }
    
    assert(SDL_GL_MakeCurrent(window, context) == 0);
    SDL_GL_SetSwapInterval(1);
//    SDL_ShowCursor(SDL_DISABLE);
    
    printf("GL_VERSION = %s\n", glGetString(GL_VERSION));
    printf("GL_VENDOR = %s\n", glGetString(GL_VENDOR));
    printf("GL_RENDERER = %s\n", glGetString(GL_RENDERER));
    printf("Started with GLSL %s\n",  glGetString(GL_SHADING_LANGUAGE_VERSION));

    glGenBuffers(1, &vertexbuffer);
    glGenBuffers(1, &uvbuffer);
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

void Renderer::updateScreen() {
    SDL_GL_SwapWindow(window);
}

float Renderer::getTotalTime() {
    return totalTime;
}

float Renderer::startFrame() {
    if (!startTime) {
        // get the time in ms passed from the moment the program started
        startTime = SDL_GetTicks();
    } else {
        delta = endTime - startTime; // how many ms for a frame
    }
    time = startTime/1000.0;
    
    if (delta < timePerFrame) {
        float sleepTime = timePerFrame - delta;
        if (sleepTime < 0) {
            sleepTime = 0;
        }
        SDL_Delay(sleepTime);
    }
    
    if (delta == 0) {
        fps = 999;
    }
    else {
        fps = 1000.0 / delta;
    }
    totalTime += delta / 1000.0;
    return delta / 1000.0;
}

void Renderer::endFrame() {
    startTime = endTime;
    endTime = SDL_GetTicks();
}

short Renderer::getFrameRate() {
    return fps;
}

void Renderer::renderFlat(RawShaderProgram &program, GLfloat x, GLfloat y, GLfloat width, GLfloat height, bool flipY) {

    GLuint u_projectionID = program.getUniformLocation("projection");
    GLuint u_time = program.getUniformLocation("time");
    
    glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 480.0f);
    
    glUniformMatrix4fv(u_projectionID, 1, GL_FALSE, &projection[0][0]);
    glUniform1f(u_time, time / 4.0);
    
    renderRect(x, y, width, height, flipY);
}

void Renderer::renderTexture(GLuint textureId, GLfloat x, GLfloat y, GLfloat width, GLfloat height, bool flipY, bool defaultProgram) {
    if (defaultProgram) {
        useProgram(*defaultTextureProgram);
        
        GLuint u_squareTextureId = defaultTextureProgram->getUniformLocation("textureSampler");
        GLuint u_projectionID = defaultTextureProgram->getUniformLocation("projection");
        
        glm::mat4 projection = glm::ortho(0.0f, WIDTH, 0.0f, HEIGHT);
        glUniformMatrix4fv(u_projectionID, 1, GL_FALSE, &projection[0][0]);
        
        glUniform1i(u_squareTextureId, 0);
        glActiveTexture(GL_TEXTURE0);
        
    }
    bindTexture(textureId);
    
    renderRect(x, y, width, height, flipY);
}

void Renderer::renderRect(GLfloat x, GLfloat y, GLfloat width, GLfloat height, bool flipY) {

    float top = flipY ? 0.0 : 1.0;
    float bottom = flipY ? 1.0 : 0.0;
    
    GLfloat xpos = x;
    GLfloat ypos = 480.0 - y - height;
    GLfloat vertices[6][4] = {
        { xpos,         ypos + height,   0.0, top },
        { xpos,         ypos,            0.0, bottom },
        { xpos + width, ypos,            1.0, bottom },
        
        { xpos,         ypos + height,   0.0, top },
        { xpos + width, ypos,            1.0, bottom },
        { xpos + width, ypos + height,   1.0, top }
    };
    
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, &vertices[0], GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Renderer::bindTexture(GLuint texId) {
    if (lastTexture != texId) {
        glBindTexture(GL_TEXTURE_2D, texId);
        lastTexture = texId;
    }
}

void Renderer::setTextProgram(RawShaderProgram *program) {
    textProgram = program;
}

void Renderer::useProgram(RawShaderProgram &program) {
    GLuint id = program.getId();
    if (lastProgram != id) {
        glUseProgram(id);
        setProgramGlobalAlpha(program);
        lastProgram = id;
    }
}

float Renderer::renderText(FontWrapper &font, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color, uint hAlign, uint vAlign)
{
    useProgram(*textProgram);
    
    struct point {
        GLfloat x;
        GLfloat y;
        GLfloat u;
        GLfloat v;
    };
    
    std::vector<point> coords(6 * text.length());
    
    GLfloat px = x;
    
    int fontSize = font.getFontSize();
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    FT_ULong previous = NULL;
    
    int n = 0;
    
    for (auto it = text.begin(); it != text.end(); it++) {
        long kerning = 0;
        FT_ULong character = *it;
        Character ch;
        int error = font.getCharacter(character, ch);
        if (error != 0) {
            printf("Error: Character %lu not available in this font.\n", character);
            continue;
        }

        // TODO: use GPOS table instead of using hardcoded kerning
        if ((character == 'e' || character == 'o') && previous == 'T'){
            kerning = 2.0f;
        }
        
        px -= kerning;
        
        GLfloat xpos = px + ((float)ch.bearing.x) * scale;
        GLfloat ypos = HEIGHT - y + (-ch.size.y + ch.bearing.y) * scale - (fontSize * 0.75) * scale;
        
        GLfloat w = ch.size.x * scale;
        GLfloat h = ch.size.y * scale;
        
        if (n + 6 < coords.size() + 1) {
            coords.at(n++) = point{xpos,     ypos + h,   ch.texCoords.x / font.texSize, ch.texCoords.y / font.texSize};
            coords.at(n++) = point{xpos,     ypos,       ch.texCoords.x / font.texSize, (ch.texCoords.y + ch.size.y) / font.texSize};
            coords.at(n++) = point{xpos + w, ypos,       (ch.texCoords.x + ch.size.x) / font.texSize, (ch.texCoords.y + ch.size.y) / font.texSize};
            coords.at(n++) = point{xpos,     ypos + h,   ch.texCoords.x / font.texSize, ch.texCoords.y / font.texSize};
            coords.at(n++) = point{xpos + w, ypos,       (ch.texCoords.x + ch.size.x) / font.texSize, (ch.texCoords.y + ch.size.y) / font.texSize};
            coords.at(n++) = point{xpos + w, ypos + h,   (ch.texCoords.x + ch.size.x) / font.texSize, ch.texCoords.y / font.texSize};
        }

        px += (ch.advance >> 6) * scale;
        previous = character;
    }
    
    // Update content of VBO memory
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, coords.size() * sizeof(point), &coords.front(), GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
                          0, // The attribute we want to configure
                          4, // size
                          GL_FLOAT, // type
                          GL_FALSE, // normalized?
                          sizeof(point), // stride
                          0 // array buffer offset
                          );
    
    std::pair<float, float> textAlign = Utils::calculateTextCenter(px - x, hAlign, vAlign, fontSize);
    glm::mat4 projection;
    
    GLuint uTextColor = textProgram->getUniformLocation("textColor");
    GLuint uTexID = textProgram->getUniformLocation("tex");
    GLuint uProjectionID = textProgram->getUniformLocation("projection");
    
    if (textProgram == defaultTextProgram) {
        glUniform1i(uTexID, 0);
        glUniform3f(uTextColor, color.x, color.y, color.z);
        glActiveTexture(GL_TEXTURE0);
        
        projection = glm::ortho(0.0f, WIDTH, 0.0f, HEIGHT);
        projection = glm::translate(projection, vec3(textAlign.first, textAlign.second, 0));
        glUniformMatrix4fv(uProjectionID, 1, GL_FALSE, &projection[0][0]);
    }
    
    bindTexture(font.texture);
    
    // Render quad
    glDrawArrays(GL_TRIANGLES, 0, n);
    
    if (textProgram == defaultTextProgram) {
        projection = glm::ortho(0.0f, WIDTH, 0.0f, HEIGHT);
        glUniformMatrix4fv(uProjectionID, 1, GL_FALSE, &projection[0][0]);
    }
    
    glDisableVertexAttribArray(0);
    bindTexture(0);
    
    return textAlign.first + px;
}

Renderer::~Renderer() {
    SDL_GL_DeleteContext(context);
}

GLuint Renderer::getVertexBuffer() {
    return vertexbuffer;
}

GLuint Renderer::getUVBuffer() {
    return uvbuffer;
}

void Renderer::drawCircle( GLfloat x, GLfloat y, GLfloat radius, GLint numberOfSides )
{
    useProgram(*textProgram);
    GLuint uTextColor = textProgram->getUniformLocation("textColor");
    
    glUniform3f(uTextColor, 1.0, 1.0, 1.0);
    
    GLint numberOfVertices = numberOfSides + 1;
    
    GLfloat doublePi = 2.0f * M_PI;
    
    std::vector<GLfloat> circleVerticesX(numberOfVertices);
    std::vector<GLfloat> circleVerticesY(numberOfVertices);
    
    for ( int i = 0; i < numberOfVertices; i++ )
    {
        circleVerticesX.at(i) = x + ( radius * cos( i * doublePi / numberOfSides ) );
        circleVerticesY.at(i) = y + ( radius * sin( i * doublePi / numberOfSides ) );
    }
    
    std::vector<GLfloat> allCircleVertices(numberOfVertices * 2);
    
    for ( int i = 0; i < numberOfVertices; i++ )
    {
        allCircleVertices.at(i * 2) = circleVerticesX.at(i);
        allCircleVertices.at(i * 2 + 1) = circleVerticesY.at(i);
    }
    
    
    
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, allCircleVertices.size() * sizeof(GLfloat), &allCircleVertices.front(), GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
                          0, // The attribute we want to configure
                          2, // size
                          GL_FLOAT, // type
                          GL_FALSE, // normalized?
                          0, // stride
                          0 // array buffer offset
                          );
    
    // Render quad
    glDrawArrays(GL_LINE_STRIP, 0, numberOfVertices);
    glDisableVertexAttribArray(0);
}

void Renderer::setGlobalAlpha(float alpha) {
    globalAlpha = alpha;
}

void Renderer::setGlobalAlpha() {
    GLuint u_globalAlpha = glGetUniformLocation(lastProgram, "globalAlpha");
    if (u_globalAlpha != -1) {
        glUniform1f(u_globalAlpha, globalAlpha);
    }
}

void Renderer::setProgramGlobalAlpha(RawShaderProgram &program) {
    GLuint u_globalAlpha = program.getUniformLocation("globalAlpha");
    if (u_globalAlpha != -1) {
        glUniform1f(u_globalAlpha, globalAlpha);
    }
}

void Renderer::createFramebuffer(GLuint &frameBuffer, GLuint &screenTexture, GLuint width, GLuint height) {
    glGenFramebuffers(1, &frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    
    glGenTextures(1, &screenTexture);
    
    // Binds the newly created texture : all future texture functions will modify this texture
    bindTexture(screenTexture);
    
    // Give an empty image to OpenGL ( the last "0" )
    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0,GL_RGB, GL_UNSIGNED_BYTE, 0);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, screenTexture, 0);
    
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        printf("Error creating framebuffer!\n");
    }
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::bindFramebuffer(GLuint frameBuffer) {
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
}

void Renderer::clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

GLuint Renderer::blurTexture(GLuint texId, float blurAmount) {
    GLfloat alpha = globalAlpha;
    setGlobalAlpha(1.0);
    bindFramebuffer(frameBuffer1);
    clear();
    
    glActiveTexture(GL_TEXTURE0);
    
    glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 480.0f);
    
    useProgram(*hBlurProgram);
    GLuint u_texture = hBlurProgram->getUniformLocation("s_texture");
    GLuint u_projectionID = hBlurProgram->getUniformLocation("projection");
    GLuint u_blurAmount = hBlurProgram->getUniformLocation("blurAmount");
    
    glUniformMatrix4fv(u_projectionID, 1, GL_FALSE, &projection[0][0]);
    glUniform1i(u_texture, 0);
    glUniform1f(u_blurAmount, blurAmount);
    
    renderTexture(texId, 0, 0, WIDTH, HEIGHT, true, false);
    
    bindFramebuffer(frameBuffer2);
    clear();
    
    useProgram(*vBlurProgram);
    u_texture = vBlurProgram->getUniformLocation("s_texture");
    u_projectionID = vBlurProgram->getUniformLocation("projection");
    u_blurAmount = hBlurProgram->getUniformLocation("blurAmount");
 
    glUniformMatrix4fv(u_projectionID, 1, GL_FALSE, &projection[0][0]);
    glUniform1i(u_texture, 0);
    glUniform1f(u_blurAmount, blurAmount);
    
    renderTexture(screenTexture1, 0, 0, WIDTH, HEIGHT, true, false);

    bindFramebuffer(0);
    setGlobalAlpha(alpha);
    return screenTexture2;
}

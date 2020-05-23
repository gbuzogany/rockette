#include "Splash.hpp"
#include <functional>
#include <memory>

Splash::Splash(Renderer *renderer, RocketteServiceImpl *service) : Scene(renderer, service) {
    
    dissolveRampTextureId = Texture::loadTGA("rkt/etc/textures/dissolve-ramp.tga");
    dissolveNoiseTextureId = Texture::loadTGA("rkt/etc/textures/noise.tga");
    splashLogo = Texture::loadTGA("rkt/etc/textures/rocket.tga");
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    animationQueue.push(new Animation("fadeIn", 0, 1.0, 1.0));
    animationQueue.push(new Animation("delay", 0, 1.0, 0.5));
    animationQueue.push(new Animation("dissolve", 0, 1.0, 2.0));
    animationQueue.push(new Animation("delay", 0, 1.0, 1.0));
    
    dissolveProgram = new ShaderProgram("rkt/etc/shaders/DissolveVertex.glsl", "rkt/etc/shaders/DissolveFragment.glsl");
}

Splash::~Splash() {
    Texture::destroyTexture(splashLogo);
    Texture::destroyTexture(dissolveRampTextureId);
    Texture::destroyTexture(dissolveNoiseTextureId);
    
    delete dissolveProgram;
}

bool Splash::update(float delta) {
    totalTime += delta;
    
    SDL_Event ev;
    while (SDL_PollEvent(&ev))
    {
        int key = ev.key.keysym.sym;
        if (ev.type == SDL_QUIT || (ev.type == SDL_KEYUP && key == 'q'))
        {
            exit(0);
            break;
        }
    }
    
    if (!animationQueue.empty()) {
        Animation *current = animationQueue.front();
        float value = current->animate(delta);
        
        if (current->getId() == "fadeIn") {
            _r->setGlobalAlpha(value);
        }
        if (current->getId() == "dissolve") {
            dissolve = value;
        }
        
        if (current->complete()) {
            animationQueue.pop();
            delete current;
        }
    }
    else {
        return false;
    }
    
    return true;
}

void Splash::setupDissolve(GLuint textureId) {
    _r->useProgram(*dissolveProgram);
    _r->setProgramGlobalAlpha(*dissolveProgram);
    
    GLuint u_baseTexture = dissolveProgram->getUniformLocation("baseTexture");
    GLuint u_noiseTexture = dissolveProgram->getUniformLocation("noiseTexture");
    GLuint u_rampTexture = dissolveProgram->getUniformLocation("rampTexture");
    GLuint u_projection = dissolveProgram->getUniformLocation("projection");
    GLuint u_dissolve = dissolveProgram->getUniformLocation("dissolve");
    
    glm::mat4 projection = glm::ortho(0.0f, WIDTH, 0.0f, HEIGHT);
    glUniformMatrix4fv(u_projection, 1, GL_FALSE, &projection[0][0]);
    
    glUniform1i(u_baseTexture, 0);
    glActiveTexture(GL_TEXTURE0);
    _r->bindTexture(textureId);
    
    glUniform1i(u_noiseTexture, 1);
    glActiveTexture(GL_TEXTURE1);
    _r->bindTexture(dissolveNoiseTextureId);
    
    glUniform1i(u_rampTexture, 2);
    glActiveTexture(GL_TEXTURE2);
    _r->bindTexture(dissolveRampTextureId);
    
    glUniform1f(u_dissolve, dissolve);
}

void Splash::render() {
    _r->clear();
    
    setupDissolve(splashLogo);
    _r->renderRect(WIDTH/2 - 175, HEIGHT/2 - 175, 350, 350, true);
}

void Splash::renderFixed() {
    
}

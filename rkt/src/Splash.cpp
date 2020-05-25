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
    
    dissolveProgram = new ShaderProgram("rkt/etc/shaders/DissolveVertex.glsl", "rkt/etc/shaders/DissolveFragment.glsl", "rkt/etc/shaders/dissolveUniforms.json");
    
    glm::mat4 projection = glm::ortho(0.0f, WIDTH, 0.0f, HEIGHT);
    dissolveProgram->setMat4Uniform("projection", projection);
    dissolveProgram->setTextureUniform("baseTexture", splashLogo);
    dissolveProgram->setTextureUniform("noiseTexture", dissolveNoiseTextureId);
    dissolveProgram->setTextureUniform("rampTexture", dissolveRampTextureId);
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

void Splash::render() {
    _r->clear();
    
    dissolveProgram->setFloatUniform("dissolve", dissolve);
    dissolveProgram->use(_r);
    _r->setGlobalAlpha();
    
    _r->renderRect(WIDTH/2 - 175, HEIGHT/2 - 175, 350, 350, true);
}

void Splash::renderFixed() {
    
}

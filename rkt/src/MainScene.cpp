#include <thread>
#include <functional>
#include <memory>
#define _USE_MATH_DEFINES
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cmath>

#include "MainScene.hpp"

#ifndef M_PI_2
#define M_PI_2 1.57079632679489661923
#endif

MainScene::MainScene(Renderer *renderer, RocketteServiceImpl *service) : Scene(renderer, service) {
    FontWrapper::loadFontFace(_r, "Roboto-Regular", "rkt/etc/fonts/Roboto-Regular.ttf");
    
    std::vector<FT_ULong> usedChars = {
        'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
        'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
        '0','1','2','3','4','5','6','7','8','9','@',(FT_ULong)176,' ','.','%','/', '!'
    };
    
    roboto = new FontWrapper("Roboto-Regular", 50, usedChars);
    robotoSmall = new FontWrapper("Roboto-Regular", 20, usedChars);
    animationQueue.push(new Animation("fadeIn", 0, 1.0, 2.0));
    
    _r->createFramebuffer(frameBuffer, screenTexture, WIDTH, HEIGHT);
}

MainScene::~MainScene() {
    delete roboto;
    delete robotoSmall;
}

bool MainScene::update(float delta) {
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
        
        if (current->complete()) {
            animationQueue.pop();
            delete current;
        }
    }
    
    return true;
}

void MainScene::render() {
    _r->clear();
    _r->renderTexture(screenTexture, 0, 0, WIDTH, HEIGHT);
  
    std::string message = "";
    _service->getStringValue("message", message);
    
    _r->renderText(*roboto, "Hello world!", WIDTH/2.0, HEIGHT/2.0, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f), CENTER);
    _r->renderText(*robotoSmall, message, WIDTH/2.0, HEIGHT/2.0 + 30.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f), CENTER);
    
    std::stringstream sfps;
    sfps << std::fixed << std::setprecision(0) << _r->getFrameRate();
    _r->renderText(*robotoSmall, sfps.str(), 0.0f, HEIGHT, 1.0f, glm::vec3(0.5f, 0.5f, 0.5f));
}

void MainScene::renderFixed() {
    _r->bindFramebuffer(frameBuffer);
    _r->clear();

    _r->bindFramebuffer(0);
    _r->setGlobalAlpha(0.0);
}

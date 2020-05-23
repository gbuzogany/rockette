#if !defined (_WIN32)
#include <unistd.h>
#endif

#include <exception>
#include <functional>
#include <vector>
#include <iostream>
#include <sstream>
#include <iomanip>

#include "Renderer.hpp"
#include "Texture.hpp"
#include "MainScene.hpp"
#include "Splash.hpp"
#include "RocketteService.hpp"

void startRocketteService(RocketteServiceImpl *service);

int main(int argc, char* argv[])
{
    Renderer r;
    r.initGraphics();
    r.initShaders();
    
    std::queue<Scene*> sceneQueue;
    RocketteServiceImpl service;
    
    std::thread rocketteServiceThread = std::thread(&startRocketteService, &service);
    
    sceneQueue.push((Scene*) new Splash(&r, &service));
    sceneQueue.push((Scene*) new MainScene(&r, &service));
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
    while (!sceneQueue.empty()) {
        bool running = true;
        
        Scene *currentScene = sceneQueue.front();
        currentScene->renderFixed();
        
        float delta;
        
        while (running) {
            delta = r.startFrame();
            
            running = currentScene->update(delta);
            if (running) {
                currentScene->render();
                r.updateScreen();
            }
            r.endFrame();
        }
        sceneQueue.pop();
    }
    SDL_Quit();
    
    return 0;
}

void startRocketteService(RocketteServiceImpl *service) {
    std::string server_address("0.0.0.0:50052");
    
    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(service);
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "RocketteService listening on " << server_address << std::endl;
    
    server->Wait();
}

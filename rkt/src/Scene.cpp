#include "Scene.hpp"

Scene::Scene(Renderer *renderer, RocketteServiceImpl *service) {
    this->_r = renderer;
    this->_service = service;
};

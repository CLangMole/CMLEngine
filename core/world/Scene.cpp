//
// Created by probn on 17/03/2025.
//

#include "Scene.h"

Scene::Scene(Camera *mainCamera) : m_mainCamera(mainCamera) {
    glEnable(GL_BLEND);
    glEnable(GL_CULL_FACE);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glCullFace(GL_BACK);

    addInstance(m_mainCamera);
}

Scene::~Scene() {
    for (Instance* i : m_instances){
        delete i;
    }
}

void Scene::render() {
    for (Instance* i : m_instances){
        i->render(m_mainCamera->getViewMatrix(), m_mainCamera->getProjectionMatrix());
    }
}

void Scene::update() {
    for (Instance* i : m_instances){
        i->update();
    }
}

void Scene::addInstance(Instance *instance) {
    m_instances.push_back(instance);
}

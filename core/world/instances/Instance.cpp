//
// Created by probn on 16/03/2025.
//

#include "Instance.h"
#include "TexturedInstance.h"

Instance::Instance(Rendering::Model *model) : m_parent(nullptr), m_name(model->getName()) {
    for (int i = 0; i < model->getMeshCount(); ++i){
        Instance* child = new TexturedInstance(model->get(i));
        addChild(child);
    }

    updateTransform();
}

Instance::Instance(std::string name) : m_name(std::move(name)) {
    updateTransform();
}

Instance::~Instance() {
    delete m_parent;
    m_parent = nullptr;

    for (Instance* i : m_children){
        delete i;
    }

    m_children.clear();
}

void Instance::addChild(Instance *instance) {
    m_children.push_back(instance);
}

Instance *Instance::getChild(int index) {
    return m_children[index];
}

void Instance::updateTransform() {
    glm::mat4 translation = glm::translate(glm::mat4{1.0f}, m_localPosition);
    glm::mat4 rotation = glm::toMat4(m_localRotation);
    glm::mat4 scale = glm::scale(glm::mat4{1.0f}, m_localScale);

    m_localMatrix = translation * rotation * scale;

    if (m_parent) {
        glm::mat4 parentWorldMatrix = m_parent->m_worldMatrix;

        m_worldMatrix = parentWorldMatrix * m_localMatrix;
        m_worldPosition = parentWorldMatrix * glm::vec4(1, m_localPosition);
        m_worldRotation = m_parent->m_worldRotation * m_localRotation;
        m_worldScale = m_parent->m_worldScale * m_localScale;
    } else {
        m_worldMatrix = m_localMatrix;
        m_worldPosition = m_localPosition;
        m_worldRotation = m_localRotation;
        m_worldScale = m_localScale;
    }

    for (Instance *i: m_children) {
        i->updateTransform();
    }
}

void Instance::update() {
    m_forward = m_worldRotation * glm::vec3(0, 0, 1);
    m_up = m_worldRotation * glm::vec3(0, 1, 0);
    m_right = m_worldRotation * glm::vec3(-1, 0, 0);
}

void Instance::render(glm::mat4 viewMat, glm::mat4 projectionMat) {
    for (Instance* i: m_children){
        i->render(viewMat, projectionMat);
    }
}

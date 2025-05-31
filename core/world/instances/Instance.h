//
// Created by probn on 16/03/2025.
//

#ifndef CMLENGINE_INSTANCE_H
#define CMLENGINE_INSTANCE_H

#define GLM_ENABLE_EXPERIMENTAL

#include "glm/glm.hpp"
#include "rendering/Model.h"
#include "rendering/Material.h"
#include <glm/gtx/quaternion.hpp>

class Instance
{
    std::string m_name = "Instance";

    std::vector<Instance *> m_children;
    Instance *m_parent{};

    glm::vec3 m_localPosition = glm::vec3(0);
    glm::vec3 m_worldPosition = glm::vec3(0);

    glm::vec3 m_localScale = glm::vec3(1);
    glm::vec3 m_worldScale = glm::vec3(1);

    glm::quat m_localRotation = glm::quat();
    glm::quat m_worldRotation = glm::quat();

    glm::mat4 m_localMatrix = glm::mat4(1);
    glm::mat4 m_worldMatrix = glm::mat4(1);

    glm::vec3 m_forward = glm::vec3(0.0, 0.0, -1.0);
    glm::vec3 m_right = glm::vec3(1.0, 0.0, 0.0);
    glm::vec3 m_up = glm::vec3(0.0, 1.0, 0.0);

    void updateTransform();

public:
    explicit Instance(std::string name);
    explicit Instance(Rendering::Model* model);
    ~Instance();

    virtual void update();
    virtual void render(glm::mat4 viewMat, glm::mat4 projectionMat);

    void addChild(Instance *instance);
    Instance *getChild(int index);

    [[nodiscard]] const std::vector<Instance *> &getChildren() const {
        return m_children;
    }

    void setChildren(const std::vector<Instance *> &children) {
        m_children = children;
        updateTransform();
    }

    [[nodiscard]] Instance *getParent() const {
        return m_parent;
    }

    void setParent(Instance *parent) {
        m_parent = parent;
        updateTransform();
    }

    [[nodiscard]] const glm::vec3 &getLocalPosition() const {
        return m_localPosition;
    }

    void setLocalPosition(const glm::vec3 &localPosition) {
        m_localPosition = localPosition;
        updateTransform();
    }

    [[nodiscard]] const glm::vec3 &getWorldPosition() const {
        return m_worldPosition;
    }

    void setWorldPosition(const glm::vec3 &worldPosition) {
        m_worldPosition = worldPosition;
        updateTransform();
    }

    [[nodiscard]] const glm::vec3 &getLocalScale() const {
        return m_localScale;
    }

    void setLocalScale(const glm::vec3 &localScale) {
        m_localScale = localScale;
        updateTransform();
    }

    [[nodiscard]] const glm::vec3 &getWorldScale() const {
        return m_worldScale;
    }

    void setWorldScale(const glm::vec3 &worldScale) {
        m_worldScale = worldScale;
        updateTransform();
    }

    [[nodiscard]] const glm::quat &getLocalRotation() const {
        return m_localRotation;
    }

    void setLocalRotation(const glm::quat &localRotation) {
        m_localRotation = glm::normalize(localRotation);
        updateTransform();
    }

    [[nodiscard]] const glm::quat &getWorldRotation() const {
        return m_worldRotation;
    }

    void setWorldRotation(const glm::quat &worldRotation) {
        m_worldRotation = worldRotation;
        updateTransform();
    }

    [[nodiscard]] const glm::mat4 &getLocalMatrix() const {
        return m_localMatrix;
    }

    void setLocalMatrix(const glm::mat4 &localMatrix) {
        m_localMatrix = localMatrix;
        updateTransform();
    }

    [[nodiscard]] const glm::mat4 &getWorldMatrix() const {
        return m_worldMatrix;
    }

    void setWorldMatrix(const glm::mat4 &worldMatrix) {
        m_worldMatrix = worldMatrix;
        updateTransform();
    }

    [[nodiscard]] const std::string &getName() const {
        return m_name;
    }

    void setName(const std::string &name) {
        m_name = name;
    }

    [[nodiscard]] glm::vec3 getLocalEulerAngles() const {
        return glm::eulerAngles(m_localRotation);
    }

    void setLocalEulerAngles(const glm::vec3 &localEulerAngles) {
        m_localRotation = glm::quat(localEulerAngles);
        updateTransform();
    }

    [[nodiscard]] glm::vec3 getWorldEulerAngles() const {
        return glm::eulerAngles(m_worldRotation);
    }

    void setWorldEulerAngles(const glm::vec3 &worldEulerAngles) {
        m_worldRotation = glm::quat(worldEulerAngles);
        updateTransform();
    }

    [[nodiscard]] const glm::vec3 &getForward() const {
        return m_forward;
    }

    [[nodiscard]] const glm::vec3 &getRight() const {
        return m_right;
    }

    [[nodiscard]] const glm::vec3 &getUp() const {
        return m_up;
    }
};


#endif //CMLENGINE_INSTANCE_H

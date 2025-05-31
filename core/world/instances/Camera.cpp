//
// Created by probn on 19/03/2025.
//

#include "Camera.h"

Camera::Camera(float rectWidth, float rectHeight, std::string name) : m_rectWidth(rectWidth), m_rectHeight(rectHeight),
                                                                      m_fov(glm::quarter_pi<float>()), m_near(0.01f), m_far(1000),
                                                                      m_projection(Perspective), m_viewMatrix(glm::mat4{1}),
                                                                      m_projectionMatrix(glm::mat4{1}), Instance(std::move(name)) {
    updateViewMatrix();
    updateProjectionMatrix();
}

void Camera::updateViewMatrix() {
    glm::vec3 worldPos = getWorldPosition();

    m_viewMatrix = glm::lookAt(worldPos, worldPos + getForward(), getUp());
}

void Camera::updateProjectionMatrix() {
    switch (m_projection) {
        case Orthographic:
            m_projectionMatrix = glm::ortho(0.0f, m_rectWidth, 0.0f, m_rectHeight, m_near, m_far);
            break;
        case Perspective:
            m_projectionMatrix = glm::perspective(glm::radians(m_fov), (float) m_rectWidth / (float) m_rectHeight,
                                                  m_near, m_far);
            break;
    }
}

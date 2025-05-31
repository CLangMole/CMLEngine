//
// Created by probn on 16/05/2025.
//

#include "TexturedInstance.h"

TexturedInstance::TexturedInstance(Rendering::Mesh *mesh) : m_mesh(mesh), Instance(mesh->getName()) {}

void TexturedInstance::render(glm::mat4 viewMat, glm::mat4 projectionMat) {
    Instance::render(viewMat, projectionMat);
    m_mesh->render(getWorldMatrix(), viewMat, projectionMat);
}

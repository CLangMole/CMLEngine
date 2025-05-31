//
// Created by probn on 16/03/2025.
//

#include "Material.h"

Rendering::Material::~Material() {
    delete m_diffuseMap;
    m_diffuseMap = nullptr;

    delete m_normalMap;
    m_normalMap = nullptr;

    delete m_specularMap;
    m_specularMap = nullptr;

    delete m_heightMap;
    m_heightMap = nullptr;

    delete m_shader;
    m_shader = nullptr;
}

Rendering::Material::Material(Rendering::ShaderProgram *shader) : m_shader(shader) {}

void Rendering::Material::render(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projMat) {
    m_shader->use();

    m_shader->set_matrix4(MODEL_MATRIX_UNIFORM_NAME, glm::value_ptr(modelMat));
    m_shader->set_matrix4(VIEW_MATRIX_UNIFORM_NAME, glm::value_ptr(viewMat));
    m_shader->set_matrix4(PROJ_MATRIX_UNIFORM_NAME, glm::value_ptr(projMat));

    m_shader->bind({{Rendering::TextureType::Diffuse,  m_diffuseMap},
                    {Rendering::TextureType::Normal,   m_normalMap},
                    {Rendering::TextureType::Specular, m_specularMap},
                    {Rendering::TextureType::Height,   m_heightMap}}, m_color);
}

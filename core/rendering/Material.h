//
// Created by probn on 16/03/2025.
//

#ifndef CMLENGINE_MATERIAL_H
#define CMLENGINE_MATERIAL_H

#include "Texture2D.h"
#include "ShaderProgram.h"
#include "glm/gtc/type_ptr.hpp"

namespace Rendering{
    class Material
    {
        Texture2D* m_diffuseMap{};
        Texture2D* m_normalMap{};
        Texture2D* m_specularMap{};
        Texture2D* m_heightMap{};

        glm::vec4 m_color = glm::vec4{1};

        ShaderProgram* m_shader;
    public:
        explicit Material(ShaderProgram* shader = ShaderProgram::defaultShader());
        ~Material();

        void render(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projMat);

        [[nodiscard]] Texture2D *getDiffuseMap() const {
            return m_diffuseMap;
        }

        void setDiffuseMap(Texture2D *diffuseMap) {
            m_diffuseMap = diffuseMap;
        }

        [[nodiscard]] Texture2D *getNormalMap() const {
            return m_normalMap;
        }

        void setNormalMap(Texture2D *normalMap) {
            m_normalMap = normalMap;
        }

        [[nodiscard]] Texture2D *getSpecularMap() const {
            return m_specularMap;
        }

        void setSpecularMap(Texture2D *specularMap) {
            m_specularMap = specularMap;
        }

        [[nodiscard]] Texture2D *getHeightMap() const {
            return m_heightMap;
        }

        void setHeightMap(Texture2D *heightMap) {
            m_heightMap = heightMap;
        }

        [[nodiscard]] const glm::vec4 &getColor() const {
            return m_color;
        }

        void setColor(const glm::vec4 &color) {
            m_color = color;
        }

        [[nodiscard]] Rendering::ShaderProgram *getShader() const {
            return m_shader;
        }

        void setShader(Rendering::ShaderProgram *shader) {
            m_shader = shader;
        }
    };
}

#endif //CMLENGINE_MATERIAL_H

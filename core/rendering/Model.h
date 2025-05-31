//
// Created by probn on 11/03/2025.
//

#ifndef CMLENGINE_MODEL_H
#define CMLENGINE_MODEL_H

#include <vector>
#include <iostream>
#include "rendering/buffer-objects/VAO.h"
#include "Material.h"
#include "asset-management/IAsset.h"

namespace Rendering
{
    struct Vertex
    {
        glm::vec3 m_position;
        glm::vec3 m_normal;
        glm::vec3 m_tangent;
        glm::vec3 m_biTangent;
        glm::vec2 m_uv;
    };

    class Mesh : public IAsset
    {
        bool m_is2D = false;

        std::vector<Vertex> m_vertices;
        std::vector<unsigned int> m_indices;

        Material* m_material;
        ShaderProgram *m_shader{};

        Rendering::VAO *m_vao;
        Rendering::VBO *m_vbo;
        Rendering::EBO *m_ebo;

        std::string m_name;

        void dispose();

    public:
        Mesh(std::string name, const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices,
             Material *material, GLenum usageType);

        ~Mesh();

        void render(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projMat);

        void recalculateTBN();

        void set2D(bool is2D){
            m_is2D = is2D;
        };

        [[nodiscard]] Material *getMaterial() const {
            return m_material;
        }

        void setMaterial(Material *material) {
            m_material = material;
        }

        [[nodiscard]] const std::string &getName() const {
            return m_name;
        }

    };

    class Model : public IAsset
    {
        std::string m_name;

        std::vector<Mesh *> m_meshes;
        std::vector<Material *> m_materials;

    public:
        Model(std::string name, std::vector<Mesh*> meshes, std::vector<Material*> materials);

        Mesh *get(int index);

        [[nodiscard]] const std::vector<Material *> &getMaterials() const {
            return m_materials;
        }

        [[nodiscard]] size_t getMeshCount() const{
            return m_meshes.size();
        }

        [[nodiscard]] const std::string &getName() const {
            return m_name;
        }


        void render();
    };
}


#endif //CMLENGINE_MODEL_H

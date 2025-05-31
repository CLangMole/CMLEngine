//
// Created by probn on 11/03/2025.
//

#include "Model.h"

Rendering::Mesh *Rendering::Model::get(int index) {
    return m_meshes[index];
}

Rendering::Mesh::Mesh(std::string name, const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices,
                      Material *material, GLenum usageType)
        : m_vertices(vertices), m_indices(indices), m_material(material), m_name(std::move(name)) {
    m_vao = new Rendering::VAO();
    m_vbo = new Rendering::VBO(usageType);
    m_ebo = new Rendering::EBO(usageType);

    m_vao->bind();
    m_vbo->init(m_vertices.size() * sizeof(Vertex), &m_vertices[0]);
    m_ebo->init(m_indices.size() * sizeof(unsigned int), &m_indices[0]);

    Rendering::VBOAttribute positionsAttribute{0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr};
    Rendering::VBOAttribute normalsAttribute{1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                                             (void *) offsetof(Vertex, m_normal)};
    Rendering::VBOAttribute tangentAttribute{2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                                             (void *) offsetof(Vertex, m_tangent)};
    Rendering::VBOAttribute biTangentAttribute{3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                                               (void *) offsetof(Vertex, m_biTangent)};
    Rendering::VBOAttribute uvAttribute{4, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, m_uv)};

    m_vao->passVertexData(positionsAttribute);
    m_vao->passVertexData(normalsAttribute);
    m_vao->passVertexData(tangentAttribute);
    m_vao->passVertexData(biTangentAttribute);
    m_vao->passVertexData(uvAttribute);

    m_vbo->unbind();

    VAO::unbind();
}

void Rendering::Mesh::render(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projMat) {
    if (m_is2D) {
        glDisable(GL_CULL_FACE);
    }

    m_material->render(modelMat, viewMat, projMat);
    m_vao->bind();
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_indices.size()), GL_UNSIGNED_INT, nullptr);
    VAO::unbind();

    if (m_is2D) {
        glEnable(GL_CULL_FACE); //TODO fix
    }
}

Rendering::Mesh::~Mesh() {
    dispose();
}

void Rendering::Mesh::dispose() {
    delete m_vao;
    m_vao = nullptr;

    delete m_vbo;
    m_vbo = nullptr;

    delete m_ebo;
    m_ebo = nullptr;

    delete m_shader;
    m_shader = nullptr;
}

void Rendering::Model::render() {
    for (auto &m: m_meshes) {
        m->render(glm::mat4(), glm::mat4(), glm::mat4());
    }
}

Rendering::Model::Model(std::string name, std::vector<Mesh *> meshes, std::vector<Material *> materials)
        : m_name(std::move(name)), m_meshes(std::move(meshes)), m_materials(std::move(materials)) {

}

void Rendering::Mesh::recalculateTBN() {
    for (int i = 0; i < m_indices.size(); i += 3) {
        glm::vec3 v1Pos = m_vertices[m_indices[i]].m_position;
        glm::vec3 v2Pos = m_vertices[m_indices[i + 1]].m_position;
        glm::vec3 v3Pos = m_vertices[m_indices[i + 2]].m_position;

        glm::vec3 normal = glm::normalize(glm::cross(v2Pos - v1Pos, v3Pos - v1Pos));
        m_vertices[m_indices[i]].m_normal = normal;
        m_vertices[m_indices[i + 1]].m_normal = normal;
        m_vertices[m_indices[i + 2]].m_normal = normal;
    }

    for (int i = 0; i < m_indices.size(); i += 3) {
        Vertex v1 = m_vertices[m_indices[i]];
        Vertex v2 = m_vertices[m_indices[i + 1]];
        Vertex v3 = m_vertices[m_indices[i + 2]];

        glm::vec3 v1Pos = v1.m_position;
        glm::vec3 v2Pos = v2.m_position;
        glm::vec3 v3Pos = v3.m_position;

        glm::vec3 edge1 = v2Pos - v1Pos;
        glm::vec3 edge2 = v3Pos - v1Pos;

        glm::vec2 uv1 = v1.m_uv;
        glm::vec2 uv2 = v2.m_uv;
        glm::vec2 uv3 = v3.m_uv;

        glm::vec2 deltaUV1 = uv2 - uv1;
        glm::vec2 deltaUV2 = uv3 - uv1;

        float f = 1 / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);
        glm::vec3 tangent = {f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x),
                             f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y),
                             f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z)};

        glm::vec3 biTangent = {f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x),
                               f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y),
                               f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z)};

        m_vertices[m_indices[i]].m_tangent = tangent;
        m_vertices[m_indices[i + 1]].m_tangent = tangent;
        m_vertices[m_indices[i + 2]].m_tangent = tangent;

        m_vertices[m_indices[i]].m_biTangent = biTangent;
        m_vertices[m_indices[i + 1]].m_biTangent = biTangent;
        m_vertices[m_indices[i + 2]].m_biTangent = biTangent;
    }
}

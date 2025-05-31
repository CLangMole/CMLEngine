//
// Created by probn on 31/05/2025.
//

#include "ModelLoader.h"

Rendering::Model *ModelLoader::loadTyped(const std::string &path) {
    const aiScene* scene = m_importer.ReadFile(path, aiProcess_CalcTangentSpace | aiProcess_Triangulate |
                                            aiProcess_JoinIdenticalVertices | aiProcess_SortByPType |
                                            aiProcess_GenSmoothNormals | aiProcess_GenUVCoords |
                                            aiProcess_OptimizeGraph | aiProcess_OptimizeMeshes |
                                            aiProcess_LimitBoneWeights | aiProcess_ValidateDataStructure |
                                            aiProcess_GlobalScale);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        throw std::runtime_error(std::string("Cannot load the scene: ") + m_importer.GetErrorString());
    }

    std::string name = scene->mName.C_Str();

    std::vector<Rendering::Material*> materials = loadMaterials(scene);
    aiNode* root = scene->mRootNode;
    std::vector<Rendering::Mesh*> meshes = processNode(root, scene, materials, m_usageType);

    return new Rendering::Model(std::move(name), meshes, materials);
}

std::vector<Rendering::Material *> ModelLoader::loadMaterials(const aiScene *scene) {
    unsigned int count = scene->mNumMaterials;

    std::vector<Rendering::Material*> result(count);

    for (unsigned int i = 0; i < count; ++i) {
        auto *material = new Rendering::Material();
        result.push_back(material);
    }

    return result;
}

std::vector<Rendering::Mesh *>
ModelLoader::processNode(aiNode *rootNode, const aiScene *scene, const std::vector<Rendering::Material *> &materials,
                         GLenum usageType) {
    std::stack<aiNode*> nodeStack;
    nodeStack.push(rootNode);

    std::vector<Rendering::Mesh*> result;

    while (!nodeStack.empty()){
        aiNode* currentNode = nodeStack.top();
        nodeStack.pop();

        for (unsigned int i = 0; i < currentNode->mNumMeshes; i++) {
            aiMesh* mesh = scene->mMeshes[currentNode->mMeshes[i]];
            result.push_back(processMesh(mesh, materials[mesh->mMaterialIndex], usageType));
        }

        for (auto it = currentNode->mChildren + currentNode->mNumChildren - 1; it >= currentNode->mChildren; --it) {
            nodeStack.push(*it);
        }
    }

    return result;
}

Rendering::Mesh *ModelLoader::processMesh(aiMesh *mesh, Rendering::Material *material, GLenum usageType) {
    std::vector<Rendering::Vertex> vertices;
    std::vector<unsigned int> indices;

    for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {

        aiVector3D assimpVertex = mesh->mVertices[i];
        glm::vec3 position = glm::vec3(assimpVertex.x, assimpVertex.y, assimpVertex.z);

        aiVector3D assimpNormal = mesh->mNormals[i];
        glm::vec3 normal = glm::vec3(assimpNormal.x, assimpNormal.y, assimpNormal.z);

        aiVector3D assimpTangent = mesh->mTangents[i];
        glm::vec3 tangent = glm::vec3(assimpTangent.x, assimpTangent.y, assimpTangent.z);

        aiVector3D assimpBiTangent = mesh->mBitangents[i];
        glm::vec3 biTangent = glm::vec3(assimpBiTangent.x, assimpBiTangent.y, assimpBiTangent.z);

        glm::vec2 uv;

        if (mesh->mTextureCoords[0]) {
            aiVector3D assimpUV = mesh->mTextureCoords[0][i];
            uv = glm::vec2(assimpUV.x, assimpUV.y);
        } else {
            uv = glm::vec2(0);
        }

        Rendering::Vertex vertex = {position, normal, tangent, biTangent, uv};
        vertices.push_back(vertex);
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
        aiFace face = mesh->mFaces[i];

        for (unsigned int j = 0; j < face.mNumIndices; ++j) {
            indices.push_back(face.mIndices[j]);
        }
    }

    return new Rendering::Mesh(mesh->mName.C_Str(), vertices, indices, material, usageType);
}

ModelLoader::ModelLoader(GLenum usageType) : m_usageType(usageType){
}

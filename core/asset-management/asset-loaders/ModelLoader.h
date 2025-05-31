//
// Created by probn on 31/05/2025.
//

#ifndef CMLENGINE_MODELLOADER_H
#define CMLENGINE_MODELLOADER_H

#include "IAssetLoader.h"
#include "rendering/Model.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <stack>

class ModelLoader : public IAssetLoader<Rendering::Model>
{
    GLenum m_usageType;

    Assimp::Importer m_importer;

    Rendering::Model *loadTyped(const std::string &path) override;

    static std::vector<Rendering::Material*> loadMaterials(const aiScene *scene);
    static std::vector<Rendering::Mesh *>
    processNode(aiNode *rootNode, const aiScene *scene, const std::vector<Rendering::Material *> &materials,
                GLenum usageType);
    static Rendering::Mesh *processMesh(aiMesh *mesh, Rendering::Material *material, GLenum usageType);

public:
    explicit ModelLoader(GLenum usageType = GL_STATIC_DRAW);
};


#endif //CMLENGINE_MODELLOADER_H

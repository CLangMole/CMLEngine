//
// Created by probn on 16/05/2025.
//

#ifndef CMLENGINE_TEXTUREDINSTANCE_H
#define CMLENGINE_TEXTUREDINSTANCE_H

#include "Instance.h"

class TexturedInstance : public Instance
{
    Rendering::Mesh *m_mesh;
public:
    explicit TexturedInstance(Rendering::Mesh* mesh);

    void render(glm::mat4 viewMat, glm::mat4 projectionMat) override;
};


#endif //CMLENGINE_TEXTUREDINSTANCE_H

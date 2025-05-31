//
// Created by probn on 17/03/2025.
//

#ifndef CMLENGINE_SCENE_H
#define CMLENGINE_SCENE_H

#include <vector>
#include "instances/Camera.h"

class Scene
{
    std::vector<Instance*> m_instances;
    Camera* m_mainCamera;

public:
    explicit Scene(Camera *mainCamera);
    ~Scene();

    void render();
    void update();

    void addInstance(Instance* instance);

    [[nodiscard]] Camera *getMainCamera() const {
        return m_mainCamera;
    }

    void setMainCamera(Camera *camera) {
        m_mainCamera = camera;
    }
};


#endif //CMLENGINE_SCENE_H

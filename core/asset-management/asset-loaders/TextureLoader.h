//
// Created by probn on 30/05/2025.
//

#ifndef CMLENGINE_TEXTURELOADER_H
#define CMLENGINE_TEXTURELOADER_H

#include "IAssetLoader.h"
#include "rendering/Texture2D.h"
#include "lodepng.h"

class TextureLoader : public IAssetLoader<Rendering::Texture2D>
{
    Rendering::Texture2D * loadTyped(const std::string &path) override;
};


#endif //CMLENGINE_TEXTURELOADER_H

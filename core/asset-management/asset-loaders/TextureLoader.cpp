//
// Created by probn on 30/05/2025.
//

#include "TextureLoader.h"

Rendering::Texture2D *TextureLoader::loadTyped(const std::string &path) {
    std::vector<unsigned char> image;
    unsigned width, height;
    unsigned error = lodepng::decode(image, width, height, path);

    if (error != 0) {
        std::cerr << "Error while decoding the texture " << error << ": " << lodepng_error_text(error) << std::endl;
        return nullptr;
    }

    return new Rendering::Texture2D(width, height, image);
}

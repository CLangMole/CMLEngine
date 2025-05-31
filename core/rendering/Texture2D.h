//
// Created by probn on 14/03/2025.
//

#ifndef CMLENGINE_TEXTURE2D_H
#define CMLENGINE_TEXTURE2D_H

#include <glad/glad.h>
#include <vector>
#include <string>

#include "asset-management/IAsset.h"

namespace Rendering
{
    struct TextureSettings
    {
        TextureSettings() = default;

        GLint m_colorSpace = GL_RGBA;
        GLfloat m_wrapMethod = GL_MIRRORED_REPEAT;
        GLfloat m_minFilteringMethod = GL_NEAREST;
        GLfloat m_magFilteringMethod = GL_LINEAR;
        bool m_generateMipMap = true;
        float m_borderColor[];
    };

    class Texture2D : public IAsset
    {
        unsigned int m_id{};
        unsigned int m_width, m_height;
        std::string m_uniformName;
        TextureSettings m_settings;
    public:
        Texture2D(unsigned int width, unsigned int height, const std::vector<unsigned char> &decoded, TextureSettings settings = TextureSettings());

        void bind() const;

        [[nodiscard]] unsigned int getId() const {
            return m_id;
        }

        [[nodiscard]] unsigned int getWidth() const {
            return m_width;
        }

        [[nodiscard]] unsigned int getHeight() const {
            return m_height;
        }
    };
}


#endif //CMLENGINE_TEXTURE2D_H

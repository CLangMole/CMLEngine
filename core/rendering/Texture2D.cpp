//
// Created by probn on 14/03/2025.
//

#include "Texture2D.h"

Rendering::Texture2D::Texture2D(unsigned int width, unsigned int height,
                                const std::vector<unsigned char> &decoded,
                                TextureSettings settings) : m_width(width), m_height(height), m_settings(settings) {
    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);

    GLint colorSpace = m_settings.m_colorSpace;
    GLfloat wrapMethod = m_settings.m_wrapMethod;

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMethod);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMethod);

    if (wrapMethod == GL_CLAMP_TO_BORDER) {
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, settings.m_borderColor);
    }

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_settings.m_minFilteringMethod);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_settings.m_magFilteringMethod);

    glTexImage2D(GL_TEXTURE_2D, 0, colorSpace, static_cast<int>(width), static_cast<int>(height), 0, colorSpace,
                 GL_UNSIGNED_BYTE, &decoded[0]);

    if (m_settings.m_generateMipMap) {
        glGenerateMipmap(GL_TEXTURE_2D);
    }
}

void Rendering::Texture2D::bind() const {
    glBindTexture(GL_TEXTURE_2D, m_id);
}

//
// Created by probn on 03/03/2025.
//

#include "VAO.h"

Rendering::VAO::VAO() {
    glGenVertexArrays(1, &m_index);
}

Rendering::VAO::~VAO() {
    dispose();
}

void Rendering::VAO::dispose() {
    glDeleteVertexArrays(1, &m_index);
}

void Rendering::VAO::bind() const {
    glBindVertexArray(m_index);
}

void Rendering::VAO::unbind() {
    glBindVertexArray(0);
}

void Rendering::VAO::enable(GLuint location) const {
    bind();
    glEnableVertexAttribArray(location);
}

void Rendering::VAO::disable() const {
    bind();
    glEnableVertexAttribArray(0);
}

void Rendering::VAO::passVertexData(VBOAttribute attribute) const {
    GLuint location = attribute.m_location;

    enable(location);

    glVertexAttribPointer(location, attribute.m_size, attribute.m_type, attribute.m_normalized,
                          attribute.m_stride, attribute.m_offset);
}

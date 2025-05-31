//
// Created by probn on 28/02/2025.
//

#ifndef CMLENGINE_BUFFEROBJECT_H
#define CMLENGINE_BUFFEROBJECT_H

#include <glad/glad.h>

namespace Rendering
{
    struct VBOAttribute
    {
        GLuint m_location;
        GLint m_size;
        GLenum m_type;
        GLboolean m_normalized;
        GLsizei m_stride;
        const void *m_offset;
    };

    template<GLenum BUFFER_TYPE>
    class BufferObject
    {
        GLuint m_index = 0;
        GLenum m_usageType;
    public:
        explicit BufferObject(GLenum usageType) : m_usageType(usageType) {
            glGenBuffers(1, &m_index);
        }

        ~BufferObject() {
            dispose();
        }

        [[nodiscard]] GLuint getIndex() const {
            return m_index;
        }

        void dispose() const {
            glDeleteBuffers(1, &m_index);
        }

        void bind() const {
            glBindBuffer(BUFFER_TYPE, m_index);
        }

        void unbind() const {
            glBindBuffer(BUFFER_TYPE, 0);
        }

        void init(size_t size, const void *data) {
            bind();
            glBufferData(BUFFER_TYPE, static_cast<GLsizeiptr>(size), data, m_usageType);
        }

        void update(size_t size, const void *data) {
            bind();
            glBufferSubData(BUFFER_TYPE, 0, static_cast<GLsizeiptr>(size), data);
        }
    };

    using VBO = BufferObject<GL_ARRAY_BUFFER>;
    using EBO = BufferObject<GL_ELEMENT_ARRAY_BUFFER>;
}

#endif //CMLENGINE_BUFFEROBJECT_H

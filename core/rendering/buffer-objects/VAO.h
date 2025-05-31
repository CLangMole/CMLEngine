//
// Created by probn on 28/02/2025.
//

#ifndef CMLENGINE_VAO_H
#define CMLENGINE_VAO_H

#include "BufferObject.h"

namespace Rendering
{
    class VAO final
    {
        GLuint m_index = 0;

    public:
        VAO();

        ~VAO();

        void dispose();

        void bind() const;

        static void unbind();

        void enable(GLuint location) const;

        void disable() const;

        void passVertexData(VBOAttribute attribute) const;
    };
}


#endif //CMLENGINE_VAO_H

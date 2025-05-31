//
// Created by probn on 02/03/2025.
//

#ifndef CMLENGINE_SHADERPROGRAM_H
#define CMLENGINE_SHADERPROGRAM_H

#include <unordered_map>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Texture2D.h"

#include "glm/glm.hpp"

#define STANDARD_SHADER_VERT_PATH "res/shaders/standardMesh.vert"
#define STANDARD_SHADER_FRAG_PATH "res/shaders/standardMesh.frag"

#define COLOR_UNIFORM "color"
#define DIFFUSE_UNIFORM_NAME "diffuseMap"
#define SPECULAR_UNIFORM_NAME "specularMap"
#define NORMAL_UNIFORM_NAME "normalMap"
#define HEIGHT_UNIFORM_NAME "heightMap"
#define MODEL_MATRIX_UNIFORM_NAME "modelMatrix"
#define VIEW_MATRIX_UNIFORM_NAME "viewMatrix"
#define PROJ_MATRIX_UNIFORM_NAME "projectionMatrix"

namespace Rendering
{
    enum TextureType
    {
        Diffuse,
        Normal,
        Specular,
        Height
    };

    class ShaderProgram
    {
        GLuint m_id;

        GLuint m_vertexShaderId;
        GLuint m_fragmentShaderId;
        GLuint m_geometryShaderId;

        std::string m_vertexShaderCode;
        std::string m_fragmentShaderCode;
        std::string m_geometryShaderCode;

        std::unordered_map<std::string, GLint> m_uniforms;

        bool m_hasGeometryShader;

        void disposeShader(GLuint id) const;
        void compileShader(GLuint id, const std::string &source) const ;

        static bool checkCompileStatus(GLuint shaderId);

        [[nodiscard]] bool checkLinkStatus() const;

        GLint getUniformLocation(const std::string& name);
        static std::string getUniformName(Rendering::TextureType type);

    public:
        ShaderProgram(const std::string& vShaderPath, const std::string& fShaderPath,
                      const std::string& gShaderPath = "");

        ~ShaderProgram();

        static ShaderProgram* defaultShader();

        void dispose() const;

        void link() const;

        void use() const;

        void set_matrix4(const std::string& name, const GLfloat* matrix, GLboolean transpose = GL_FALSE);
        void set_int(const std::string& name, GLint value);
        void set_uint(const std::string& name, GLuint value);
        void set_float(const std::string& name, GLfloat value);
        void set_vec(const std::string& name, GLfloat x, GLfloat y);
        void set_vec(const std::string& name, GLfloat x, GLfloat y, GLfloat z);
        void set_vec(const std::string& name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
        void bind(const std::unordered_map<TextureType, Texture2D *> &textures, glm::vec4 color);

        [[nodiscard]] GLuint getId() const {
            return m_id;
        }
    };
}

#endif //CMLENGINE_SHADERPROGRAM_H

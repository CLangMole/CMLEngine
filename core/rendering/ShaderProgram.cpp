//
// Created by probn on 02/03/2025.
//

#include "ShaderProgram.h"

Rendering::ShaderProgram::ShaderProgram(const std::string& vShaderPath, const std::string& fShaderPath, const std::string& gShaderPath)
        : m_id(glCreateProgram()),
          m_vertexShaderId(glCreateShader(GL_VERTEX_SHADER)), m_fragmentShaderId(glCreateShader(GL_FRAGMENT_SHADER)),
          m_hasGeometryShader(!gShaderPath.empty()) {
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    std::ifstream gShaderFile;

    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    gShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        vShaderFile.open(vShaderPath);
        fShaderFile.open(fShaderPath);

        std::stringstream vShaderStream, fShaderStream, gShaderStream;

        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        m_vertexShaderCode = vShaderStream.str();
        m_fragmentShaderCode = fShaderStream.str();

        if (m_hasGeometryShader){
            gShaderFile.open(gShaderPath);
            gShaderStream << gShaderFile.rdbuf();
            gShaderFile.close();
            m_geometryShaderCode = gShaderStream.str();
        }
    }
    catch (std::ifstream::failure& e)
    {
        std::cerr << "Shader could not be read: " << e.what() << std::endl;
    }

    if (m_hasGeometryShader) {
        m_geometryShaderId = glCreateShader(GL_GEOMETRY_SHADER);
    }
}

Rendering::ShaderProgram::~ShaderProgram() {
    dispose();
}

void Rendering::ShaderProgram::dispose() const {
    ShaderProgram::disposeShader(m_vertexShaderId);
    ShaderProgram::disposeShader(m_fragmentShaderId);

    if (m_hasGeometryShader) {
        ShaderProgram::disposeShader(m_geometryShaderId);
    }
}

void Rendering::ShaderProgram::disposeShader(GLuint id) const {
    glDetachShader(m_id, id);
    glDeleteShader(id);
}

void Rendering::ShaderProgram::compileShader(GLuint id, const std::string &source) const {
    char const *sourcePtr = source.c_str();
    glShaderSource(id, 1, &sourcePtr, nullptr);
    glCompileShader(id);

    if (!checkCompileStatus(id)) {
        throw std::runtime_error("Shader compilation failed");
    }

    glAttachShader(m_id, id);
}

bool Rendering::ShaderProgram::checkCompileStatus(GLuint shaderId) {
    GLint success;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);

    if (!success) {
        GLint logLength;
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLength);

        std::string errorLog(logLength, '\0');
        glGetShaderInfoLog(shaderId, logLength, nullptr, &errorLog[0]);

        std::cerr << "Shader compilation error:\n" << errorLog << std::endl;
        return false;
    }

    return true;
}

void Rendering::ShaderProgram::link() const {
    compileShader(m_vertexShaderId, m_vertexShaderCode);
    compileShader(m_fragmentShaderId, m_fragmentShaderCode);

    if (m_hasGeometryShader) {
        compileShader(m_geometryShaderId, m_geometryShaderCode);
    }

    glLinkProgram(m_id);

    if (!checkLinkStatus()) {
        throw std::runtime_error("Shader program linking failed");
    }
}

bool Rendering::ShaderProgram::checkLinkStatus() const {
    GLint success;
    glGetProgramiv(m_id, GL_LINK_STATUS, &success);

    if (!success) {
        GLint logLength;
        glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &logLength);

        if (logLength > 0) {
            std::string errorLog(logLength, '\0');
            glGetProgramInfoLog(m_id, logLength, nullptr, errorLog.data());
            std::cerr << "Program linking failed:\n" << errorLog << std::endl;
        }

        return false;
    }

    return true;
}

GLint Rendering::ShaderProgram::getUniformLocation(const std::string &name) {
    if (const auto it = m_uniforms.find(name); it != m_uniforms.end()) {
        return it->second;
    }

    return m_uniforms[name] = glGetUniformLocation(m_id, name.c_str());
}

void Rendering::ShaderProgram::use() const {
    glUseProgram(m_id);
}

void Rendering::ShaderProgram::set_matrix4(const std::string &name, const GLfloat *matrix, const GLboolean transpose) {
    glUniformMatrix4fv(getUniformLocation(name), 1, transpose, matrix);
}

void Rendering::ShaderProgram::set_int(const std::string &name, const GLint value) {
    glUniform1i(getUniformLocation(name), value);
}

void Rendering::ShaderProgram::set_uint(const std::string &name, const GLuint value) {
    glUniform1ui(getUniformLocation(name), value);
}

void Rendering::ShaderProgram::set_float(const std::string &name, const GLfloat value) {
    glUniform1f(getUniformLocation(name), value);
}

void Rendering::ShaderProgram::set_vec(const std::string &name, GLfloat x, GLfloat y) {
    glUniform2f(getUniformLocation(name), x, y);
}

void Rendering::ShaderProgram::set_vec(const std::string &name, GLfloat x, GLfloat y, GLfloat z) {
    glUniform3f(getUniformLocation(name), x, y, z);
}

void Rendering::ShaderProgram::set_vec(const std::string &name, GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
    glUniform4f(getUniformLocation(name), x, y, z, w);
}

void Rendering::ShaderProgram::bind(const std::unordered_map<TextureType, Texture2D *> &textures, glm::vec4 color) {
//    use();

    set_vec(COLOR_UNIFORM, color.x, color.y, color.z, color.w);

    int i = 0;

    for (const auto &[type, texture]: textures) {
        std::string uniformName = getUniformName(type);
        bool hasTex = texture != nullptr;
        set_int("has_" + uniformName, hasTex);

        if (hasTex) {
            int id = static_cast<int>(texture->getId());

            glActiveTexture(GL_TEXTURE0 + i);
            set_int(uniformName, id);
            texture->bind();
            i++;
        }
    }

    glActiveTexture(GL_TEXTURE0);
}

Rendering::ShaderProgram *Rendering::ShaderProgram::defaultShader() {
    return new ShaderProgram(STANDARD_SHADER_VERT_PATH, STANDARD_SHADER_FRAG_PATH);
}

std::string Rendering::ShaderProgram::getUniformName(Rendering::TextureType type) {
    switch (type) {
        case Diffuse:
            return DIFFUSE_UNIFORM_NAME;
        case Normal:
            return NORMAL_UNIFORM_NAME;
        case Specular:
            return SPECULAR_UNIFORM_NAME;
        case Height:
            return HEIGHT_UNIFORM_NAME;
    }

    return "";
}

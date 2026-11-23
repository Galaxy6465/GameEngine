#pragma once

#include "utils/u_camera.h"

#include <glad/glad.h>

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

namespace Utils {

class Shader {
public:
    Shader() = default;
    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;

    Shader(Shader&& other) noexcept : m_Program(std::exchange(other.m_Program, 0)) {}

    Shader& operator=(Shader&& other) noexcept
    {
        if (this != &other) {
            Release();
            m_Program = std::exchange(other.m_Program, 0);
        }
        return *this;
    }

    ~Shader()
    {
        Release();
    }

    void LoadFromFiles(const std::string& vertexPath, const std::string& fragmentPath)
    {
        const std::string vertexSource = ReadFile(vertexPath);
        const std::string fragmentSource = ReadFile(fragmentPath);
        const GLuint vertexShader = Compile(GL_VERTEX_SHADER, vertexSource, vertexPath);
        GLuint fragmentShader = 0;

        try {
            fragmentShader = Compile(GL_FRAGMENT_SHADER, fragmentSource, fragmentPath);
            const GLuint program = glCreateProgram();
            if (program == 0) {
                throw std::runtime_error("Failed to create shader program");
            }

            glAttachShader(program, vertexShader);
            glAttachShader(program, fragmentShader);
            glLinkProgram(program);

            GLint success = GL_FALSE;
            glGetProgramiv(program, GL_LINK_STATUS, &success);
            if (success != GL_TRUE) {
                GLint logLength = 0;
                glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
                std::string log(static_cast<std::size_t>(logLength), '\0');
                glGetProgramInfoLog(program, logLength, nullptr, log.data());
                glDeleteProgram(program);
                throw std::runtime_error("Failed to link shader program:\n" + log);
            }

            Release();
            m_Program = program;
        } catch (...) {
            glDeleteShader(vertexShader);
            if (fragmentShader != 0) {
                glDeleteShader(fragmentShader);
            }
            throw;
        }

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    void Use() const
    {
        EnsureLoaded();
        glUseProgram(m_Program);
    }

    void SetBool(const std::string& name, bool value) const
    {
        SetInt(name, value ? 1 : 0);
    }

    void SetInt(const std::string& name, int value) const
    {
        glUniform1i(UniformLocation(name), value);
    }

    void SetFloat(const std::string& name, float value) const
    {
        glUniform1f(UniformLocation(name), value);
    }

    void SetVec3(const std::string& name, float x, float y, float z) const
    {
        glUniform3f(UniformLocation(name), x, y, z);
    }

    void SetVec4(const std::string& name, float x, float y, float z, float w) const
    {
        glUniform4f(UniformLocation(name), x, y, z, w);
    }

    void SetMat4(const std::string& name, const Mat4& value) const
    {
        glUniformMatrix4fv(UniformLocation(name), 1, GL_FALSE, value.Data());
    }

    GLuint GetProgram() const { return m_Program; }

    void Release()
    {
        if (m_Program != 0) {
            glDeleteProgram(m_Program);
            m_Program = 0;
        }
    }

private:
    static std::string ReadFile(const std::string& path)
    {
        std::ifstream file(path);
        if (!file) {
            throw std::runtime_error("Unable to open shader file: " + path);
        }

        std::ostringstream contents;
        contents << file.rdbuf();
        if (file.bad()) {
            throw std::runtime_error("Failed while reading shader file: " + path);
        }
        return contents.str();
    }

    static GLuint Compile(GLenum type, const std::string& source, const std::string& path)
    {
        const GLuint shader = glCreateShader(type);
        if (shader == 0) {
            throw std::runtime_error("Failed to create shader for: " + path);
        }

        const char* sourceText = source.c_str();
        glShaderSource(shader, 1, &sourceText, nullptr);
        glCompileShader(shader);

        GLint success = GL_FALSE;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (success != GL_TRUE) {
            GLint logLength = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
            std::string log(static_cast<std::size_t>(logLength), '\0');
            glGetShaderInfoLog(shader, logLength, nullptr, log.data());
            glDeleteShader(shader);
            throw std::runtime_error("Failed to compile shader " + path + ":\n" + log);
        }
        return shader;
    }

    GLint UniformLocation(const std::string& name) const
    {
        EnsureLoaded();
        const GLint location = glGetUniformLocation(m_Program, name.c_str());
        if (location < 0) {
            throw std::runtime_error("Shader uniform not found: " + name);
        }
        return location;
    }

    void EnsureLoaded() const
    {
        if (m_Program == 0) {
            throw std::logic_error("Shader has not been loaded");
        }
    }

    GLuint m_Program = 0;
};

} // namespace Utils

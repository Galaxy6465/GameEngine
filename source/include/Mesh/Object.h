#pragma once

#include <vector>
#include <string>

#include "utils/shader_m.h"
#include "utils/texture_m.h"

#include <glm/glm.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoord;
};

struct ObjectData {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    GLuint VAO = 0; // Vertex Array Object
    GLuint VBO = 0;
    GLuint EBO = 0;

};

struct ObjectValues {
    glm::vec3 position = { 0.0f, 0.0f, 0.0f };
    glm::vec3 scale = { 1.0f, 1.0f, 1.0f };
    glm::vec3 rotation = { 0.0f, 0.0f, 0.0f };  
};

class Object
{
public:
    Object() = default;

    ~Object();

    void Init();

    void Draw();

    ObjectData& GetObjectData() { return m_data; }
    const ObjectData& GetObjectData() const { return m_data; }

    ObjectValues& GetObjectValues() { return m_Values; }
    const ObjectValues& GetObjectValues() const { return m_Values; }

    void SetShader(std::string vs, std::string fs);

    void SetTextures(std::string texpath);

private:   
    std::vector<float> textureCoords;
    std::string texturePath;


public:
    ObjectData m_data;
    ObjectValues m_Values;

    Shader* shader = nullptr;
    Texture* texture = nullptr;

};
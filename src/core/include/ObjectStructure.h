#pragma once

#include <glm/glm.hpp>
#include <vector>
#include "shader_m.h"
#include "texture_m.h"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

struct ObjectData {
    GLuint VAO;
    std::vector<float> vertices;
    std::vector<GLuint> indices;
    //? suggestion use unique_pointer go read when i have 7fps for 10000 objects
    Shader* shader = nullptr;
    Texture* texture = nullptr;
};

struct ObjectValues {
    glm::vec3 color = glm::vec3(1.0f);
    glm::vec3 size = glm::vec3(1.0f);
    glm::vec3 position = glm::vec3(0.0f);

    struct Material {
        float ambient = 1.0f;
        float diffuse = 1.0f;
        float specular = 1.0f;
        float shininess = 1.0f;
    };
};

struct LightValues {
    glm::vec3 color = glm::vec3(1.0f);
    glm::vec3 size = glm::vec3(1.0f);
    glm::vec3 position = glm::vec3(0.0f);

    struct ColorProps {
        float ambient = 1.0f;
        float diffuse = 1.0f;
        float specular = 1.0f;
        float shininess = 1.0f;
    };
};

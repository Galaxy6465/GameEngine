#pragma once

#include <vector>
#include <glad/glad.h>
#include "graphics/shader_m.h"
#include "graphics/texture_m.hpp"
#include "graphics/camera.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct EngineContext {
    float screenWidth = 1500.0f;
    float screenHeight = 800.0f;
    const char* title = "Custom Engine";

    Camera camera = Camera(glm::vec3(0.0f, 1.0f, 1.0f));

};

struct ObjectData {
    GLuint VAO;
    std::vector<float> vertices;
    std::vector<GLuint> indices;
    //? suggestion use unique_pointer go read when i have 7fps for 10000 objects
    Shader* shader = nullptr;
    Texture* texture = nullptr;
};

struct ObjectValues {
    glm::vec3 color;
    glm::vec3 size;
    glm::vec3 position;

    struct Material {
        float ambient = 1.0f;
        float diffuse = 1.0f;
        float specular = 1.0f;
        float shininess = 1.0f;
    };
};

struct LightValues {
    glm::vec3 color;
    glm::vec3 size;
    glm::vec3 position;
};



struct ObjectValues_DataBase {
    std::vector<ObjectValues> cubeList = {
        { glm::vec3(1.0f, 0.2f, 0.2f), glm::vec3(1.0f), glm::vec3(0.0f, 0.0f, 0.0f) },   // Center (Red)
        { glm::vec3(0.2f, 1.0f, 0.2f), glm::vec3(0.8f), glm::vec3(2.0f, 0.5f, -1.5f) },  // Right (Green)
        { glm::vec3(0.2f, 0.4f, 1.0f), glm::vec3(1.2f), glm::vec3(-2.5f, 0.0f, -2.0f) }, // Left (Blue)
        { glm::vec3(1.0f, 1.0f, 0.2f), glm::vec3(0.5f), glm::vec3(1.0f, 1.5f, -3.0f) },  // Top-Right (Yellow)
        { glm::vec3(1.0f, 0.2f, 1.0f), glm::vec3(0.9f), glm::vec3(-1.5f, -0.5f, -4.0f) },// Bottom-Left (Magenta)
        { glm::vec3(0.2f, 1.0f, 1.0f), glm::vec3(1.5f), glm::vec3(0.0f, 2.0f, -5.0f) },  // Far Center (Cyan)
        { glm::vec3(1.0f, 0.5f, 0.0f), glm::vec3(0.7f), glm::vec3(3.5f, -1.0f, -2.5f) }, // Far Right (Orange)
        { glm::vec3(0.5f, 0.2f, 1.0f), glm::vec3(1.1f), glm::vec3(-3.0f, 1.2f, -3.5f) }, // Upper Left (Purple)
        { glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(2.0f), glm::vec3(0.0f, -2.0f, -6.0f) }, // Ground / Floor-ish (Gray)
        { glm::vec3(0.1f, 0.9f, 0.5f), glm::vec3(0.6f), glm::vec3(1.5f, 1.0f, -1.0f) }   // Close Right (Teal)
    };
};

struct Object_c {
    std::string name;
    ObjectData object;
    ObjectValues values;
};
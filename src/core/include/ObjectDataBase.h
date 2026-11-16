#pragma once
#include <vector>
#include "ObjectStructure.h"

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
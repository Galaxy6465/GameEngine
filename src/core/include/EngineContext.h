#pragma once

#include "ObjectStructure.h"

#include <vector>
#include "camera.h"

struct EngineContext {
    float screenWidth = 1500.0f;
    float screenHeight = 800.0f;
    const char* title = "Custom Engine";

    Camera camera = Camera(glm::vec3(0.0f, 1.0f, 1.0f));

};




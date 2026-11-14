#ifndef ENGINE_HPP
#define ENGINE_HPP

// 1. Core and Graphics Dependencies
#include "core/EngineContext.hpp"
#include "io/Input.hpp"
#include "ui/ImGuiLayer.hpp"
#include "graphics/MeshGenerator.hpp"

// 2. External Libraries & Standard Headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include "graphics/shader_m.h"
#include "graphics/texture_m.hpp"
#include <vector>
#include <iostream>

class Engine {
private:
    
    GLFWwindow* s_window;
    void OPENGL_INIT();

    int Init();

    void Update();

    void CreateWindow();

    void Clean();

public:
    Engine();
    
    void run();
};

#endif
#ifndef ENGINE_HPP
#define ENGINE_HPP

// 1. Core and Graphics Dependencies (Matching modular include paths)
#include "EngineContext.h"
#include "Input.h"
#include "ImGuiLayer.h"
#include "MeshGenerator.h"
#include "ObjectDataBase.h"
#include "ObjectStructure.h"
#include "ImGUI4Object.h"
#include "Renderer.h"

// 2. External Libraries & Standard Headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include "shader_m.h"
#include "texture_m.h"
#include <vector>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

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
#pragma once

#include "ImGUIIncludes.h"
#include "EngineContext.h"
#include <GLFW/glfw3.h>

class ImGuiLayer {
public:
    static void Init(GLFWwindow* window, EngineContext& context);
    static void Begin();
    static void End();
    static void Shutdown();
};
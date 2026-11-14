#pragma once

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include "core/EngineContext.hpp"
#include <GLFW/glfw3.h>


class ImGuiLayer {
public:
    static void Init(GLFWwindow* window);
    static void Begin();
    static void End();
    static void Shutdown();
};
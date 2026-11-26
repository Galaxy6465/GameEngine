#pragma once
#include "Layers/Layer.h"
#include "Core/Log.h"
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

class MainImGuiOverlay : public Layer {
public:
    MainImGuiOverlay(GLFWwindow* window, float* cubeColor = nullptr)
        : Layer("MainImGuiOverlay"), m_Window(window), m_CubeColor(cubeColor) {}

    void OnAttach() override {
        glfwMakeContextCurrent(m_Window);

        IMGUI_CHECKVERSION();
        m_Context = ImGui::CreateContext();
        ImGui::SetCurrentContext(m_Context);

        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
        
        ImGui::StyleColorsDark();

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
        ImGui_ImplOpenGL3_Init("#version 330");

        APP_INFO("ImGuiOverlay Attached!");
    }

    void OnDetach() override {
        glfwMakeContextCurrent(m_Window);
        ImGui::SetCurrentContext(m_Context);

        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext(m_Context);

        APP_INFO("ImGuiOverlay Detached!");
    }

    void OnUpdate() override {}

    void OnRender() override {
        // Ensure this window's OpenGL & ImGui contexts are active
        glfwMakeContextCurrent(m_Window);
        ImGui::SetCurrentContext(m_Context);

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::DockSpaceOverViewport(
            0,
            ImGui::GetMainViewport(),
            ImGuiDockNodeFlags_PassthruCentralNode);

        // --- UI Widgets ---
        ImGui::Begin("Engine Inspector");
        ImGui::Text("FPS: %.1f (%.3f ms)", ImGui::GetIO().Framerate, 1000.0f / ImGui::GetIO().Framerate);
        if (m_CubeColor) {
            ImGui::ColorEdit4("Cube Color", m_CubeColor);
        }
        ImGui::Checkbox("Show ImGui Demo Window", &m_ShowDemoWindow);
        ImGui::End();

        if (m_ShowDemoWindow) {
            ImGui::ShowDemoWindow(&m_ShowDemoWindow);
        }

        // Render ImGui draw data on top of OpenGL
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }
    }

private:
    GLFWwindow* m_Window = nullptr;
    ImGuiContext* m_Context = nullptr;
    float* m_CubeColor = nullptr;
    bool m_ShowDemoWindow = false;
};

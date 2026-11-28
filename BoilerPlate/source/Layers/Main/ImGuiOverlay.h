#pragma once
#include "Layers/Layer.h"
#include "Core/Log.h"
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "Core/Settings.h"

#include <httplib.h>

class MainImGuiOverlay : public Layer {
public:
    MainImGuiOverlay(GLFWwindow* window, float* cubeColor = nullptr)
        : Layer("MainImGuiOverlay"), m_Window(window) {}

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

        //! =======================================|| APP BAR ||=====================================||
        static bool m_ShowInspector;
        static bool m_ShowElements;
        static bool m_ShowDemoWindow;

        if (ImGui::BeginMainMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("New Project", "Ctrl+N")) { /* Action */ }
                if (ImGui::MenuItem("Open...", "Ctrl+O"))     { /* Action */ }
                if (ImGui::MenuItem("Save", "Ctrl+S"))        { /* Action */ }
                ImGui::Separator();
                if (ImGui::MenuItem("Exit"))                  { /* Close app */ }
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("View")) {
                ImGui::MenuItem("Engine Inspector", nullptr, &m_ShowInspector);
                ImGui::MenuItem("Element Storage", nullptr, &m_ShowElements);
                ImGui::MenuItem("ImGui Demo Window", nullptr, &m_ShowDemoWindow);
                ImGui::EndMenu();
            }

            if(ImGui::BeginMenu("Settings")) {
                if(ImGui::Checkbox("VSync", &Settings::VSync)) {

                }
                ImGui::EndMenu();
            }

            // Optional: Right-aligned action button (e.g., Play / Preview App)
            float buttonWidth = 70.0f;
            ImGui::SetCursorPosX(ImGui::GetWindowWidth() - buttonWidth - ImGui::GetStyle().WindowPadding.x);
            if (ImGui::Button("Preview", ImVec2(buttonWidth, 0))) {
                // Trigger app preview
            }

            ImGui::EndMainMenuBar();
        }

        //! =====================================|| INSPECTOR WINDOW ||=====================================||
            
        ImGui::SetNextWindowSize(ImVec2(350, 200), ImGuiCond_FirstUseEver);

        ImGui::Begin("Engine Inspector");
        ImGui::Text("FPS: %.1f (%.3f ms)", ImGui::GetIO().Framerate, 1000.0f / ImGui::GetIO().Framerate);
        ImGui::ColorEdit4("Background Color", Settings::wind_Settings[0].backgroundColor.col);
        ImGui::Checkbox("Show ImGui Demo Window", &m_ShowDemoWindow);
        ImGui::End();

        if (m_ShowDemoWindow) {
            ImGui::ShowDemoWindow(&m_ShowDemoWindow);
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            GLFWwindow* backup_current_context = glfwGetCurrentContext(); 
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }

        //! =====================================|| SIDE BAR ||=====================================||
    
        
    }

private:
    GLFWwindow* m_Window = nullptr;
    ImGuiContext* m_Context = nullptr;
};

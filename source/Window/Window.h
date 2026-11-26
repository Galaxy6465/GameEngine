#pragma once

#include "Application/ApplicationContext.h"
#include "Layers/LayerStack.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
public:
    Window(const Specifications::WindowContext& winContext, GLFWwindow* sharedWindow);
    virtual ~Window();

    void Init();

    
    bool ShouldClose() {
        return !m_win_Running || glfwWindowShouldClose(m_Window) || (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS); 
    }

    const char* GetWindowName() { return m_Context.win_Name; }
    

    GLFWwindow* GetNativeWindow() const { return m_Window; }

    virtual void PushLayer(std::unique_ptr<Layer> layer);
    virtual void PushOverlay(std::unique_ptr<Layer> overlay);

    virtual void OnUpdate();
    virtual void OnRender();
    virtual void Clean();

private:
    bool m_win_Running = true;
protected:
    virtual void OnScroll(double xOffset, double yOffset);

    Specifications::WindowContext m_Context;
    GLFWwindow* m_Window = nullptr;
    GLFWwindow* m_sharedWindow = nullptr;
    LayerStack m_LayerStack;
};
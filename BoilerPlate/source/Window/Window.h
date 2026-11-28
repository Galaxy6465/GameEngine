#pragma once

#include "windowContext.h"
#include "Layers/LayerStack.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

class Window {
public:
    Window(const WindowContext& ctx, GLFWwindow* sharedWindow);
    virtual ~Window();

    void Init();

    
    void ShouldClose() {
        if(glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
            glfwSetWindowShouldClose(m_Window, true);
        }
        glfwWindowShouldClose(m_Window);
    }

    const char* GetWindowName() { return winCtx.name; }
    

    GLFWwindow* GetNativeWindow() const { return m_Window; }

    virtual void PushLayer(std::unique_ptr<Layer> layer);
    virtual void PushOverlay(std::unique_ptr<Layer> overlay);

    virtual void OnUpdate();
    virtual void OnRender();
    virtual void Clean();

protected:
    virtual void OnScroll(double xOffset, double yOffset);

    GLFWwindow* m_Window = nullptr;
    GLFWwindow* m_sharedWindow = nullptr;
    LayerStack m_LayerStack;

    WindowContext winCtx;
};
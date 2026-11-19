#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct WindowContext {
    const char* title = nullptr;
    bool Running = false;
    float width = 900;
    float height = 600;
};

class Window {
public:
    Window(const char* title, float width, float height);
    ~Window() = default;

    virtual void Init(GLFWwindow* sharedWindow = nullptr);

    virtual void OnUpdate();

    virtual void CreateContext();
    GLFWwindow* GetWindow() { return m_window; }

    virtual void CreateWindow();
protected:
    WindowContext win_ctx;
    GLFWwindow* m_window = nullptr;
};
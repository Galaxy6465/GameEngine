#include "Window/Window.h"
#include "Core/Log.h"

#include "Core/Settings.h"

Window::Window(const WindowContext& ctx, GLFWwindow* sharedWindow)
{
    winCtx.name = ctx.name;
    winCtx.width = ctx.width;
    winCtx.height = ctx.height;

    m_sharedWindow = sharedWindow;

    m_Window = glfwCreateWindow(ctx.width, ctx.height, ctx.name, nullptr, m_sharedWindow);
    if(!m_Window){
        WIN_ERROR("INITIALIZE::FAILED::", ctx.name);
    }

    // Bind THIS specific Window instance to its GLFWwindow* handle
    glfwSetWindowUserPointer(m_Window, this);

    // Per-window resize callback
    glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* win, int w, int h) {
        auto* self = static_cast<Window*>(glfwGetWindowUserPointer(win));
        self->winCtx.width = w;
        self->winCtx.height = h;
    });

    glfwSetScrollCallback(m_Window, [](GLFWwindow* win, double xOffset, double yOffset) {
        auto* self = static_cast<Window*>(glfwGetWindowUserPointer(win));
        self->OnScroll(xOffset, yOffset);
    });

    // Per-window VSync requires making THIS window's context current first
    glfwMakeContextCurrent(m_Window);
    bool VSync = true;
    glfwSwapInterval(VSync ? 1 : 0);
}

Window::~Window()
{
    if (m_Window) {
        glfwMakeContextCurrent(m_Window);
        m_LayerStack.Clear();
        glfwDestroyWindow(m_Window);
        m_Window = nullptr;
    } else {
        m_LayerStack.Clear();
    }
}

void Window::PushLayer(std::unique_ptr<Layer> layer)
{
    glfwMakeContextCurrent(m_Window);
    m_LayerStack.PushLayer(std::move(layer));
}

void Window::PushOverlay(std::unique_ptr<Layer> overlay)
{
    glfwMakeContextCurrent(m_Window);
    m_LayerStack.PushOverlay(std::move(overlay));
}

void Window::Init()
{
    
}

void Window::OnUpdate()
{
    for (auto& layer : m_LayerStack) {
        layer->OnUpdate();
    }
}
void Window::OnRender()
{
    // 1. Make this window's OpenGL context current
    glfwMakeContextCurrent(m_Window);

    // 2. Ensure the viewport matches the window size
    int width, height;
    glfwGetFramebufferSize(m_Window, &width, &height);
    glViewport(0, 0, width, height);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // --- Your OpenGL draw calls go here ---
    // Render every layer attached to THIS window
    for (auto& layer : m_LayerStack) {
        layer->OnRender();
    }

    // 4. Present the rendered frame
    glfwSwapBuffers(m_Window);
}

void Window::Clean()
{

}

void Window::OnScroll(double, double)
{
}
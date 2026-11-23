#include "Window/Window.h"
#include "Core/Log.h"
#include "Application/ApplicationContext.h"

Window::Window(const Specifications::WindowContext& winContext, GLFWwindow* sharedWindow)
{
    m_Context.win_Name = winContext.win_Name;
    m_Context.win_Width = winContext.win_Width;
    m_Context.win_Height = winContext.win_Height;

    m_sharedWindow = sharedWindow;

    m_Window = glfwCreateWindow(m_Context.win_Width, m_Context.win_Height, m_Context.win_Name, nullptr, m_sharedWindow);
    if(!m_Window){
        WIN_ERROR("INITIALIZE::FAILED::", m_Context.win_Name);
    }

    // Bind THIS specific Window instance to its GLFWwindow* handle
    glfwSetWindowUserPointer(m_Window, this);

    // Per-window resize callback
    glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* win, int w, int h) {
        auto* self = static_cast<Window*>(glfwGetWindowUserPointer(win));
        self->m_Context.win_Width = w;
        self->m_Context.win_Height = h;
    });

    glfwSetScrollCallback(m_Window, [](GLFWwindow* win, double xOffset, double yOffset) {
        auto* self = static_cast<Window*>(glfwGetWindowUserPointer(win));
        self->OnScroll(xOffset, yOffset);
    });

    // Per-window VSync requires making THIS window's context current first
    glfwMakeContextCurrent(m_Window);
    glfwSwapInterval(Specifications::appSpecifiactions.app_VSync ? 1 : 0);
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

    // 3. Clear the screen with a solid color (e.g., dark gray/blue)
    glClearColor(0.15f, 0.15f, 0.18f, 1.0f);
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
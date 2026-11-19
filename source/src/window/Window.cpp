#include "window/Window.h"
#include "Debug/Debug.h"

Window::Window(const char* title, float width, float height)
{
    win_ctx.title = title;
    win_ctx.width = width;
    win_ctx.height = height;
}

void Window::Init(GLFWwindow* sharedWindow)
{
    m_window = glfwCreateWindow(win_ctx.width, win_ctx.height, win_ctx.title, nullptr, sharedWindow);
    if(!m_window)
    {
        APP_ERROR("Failed to Initialize Window : ", win_ctx.title);
        return;
    }
    APP_TRACE("WINDOW::INITIALIZED : ", win_ctx.title);
}

void Window::CreateContext()
{
    glfwMakeContextCurrent(m_window);
}


void Window::OnUpdate()
{
    APP_TRACE("WINDOW::UPDATING : ", win_ctx.title);
}

void Window::CreateWindow()
{
    APP_INFO("Running Window : ", win_ctx.title);
}
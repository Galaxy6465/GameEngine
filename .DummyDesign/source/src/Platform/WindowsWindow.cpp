/*

#include "Platform/WindowsWindow.h"
#include <iostream>
#include "Event/ApplicationEvent.h"


namespace GalaxyEngine {

    static bool GLFWInitialized = false;

    // Window* Window::Create(const WindowProps& props)
    // {
    //     return new WindowsWindow(props);
    // }

	WindowsWindow::WindowsWindow(const WindowProps& props) { Init(props); }

	WindowsWindow::~WindowsWindow() { Shutdown(); }

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		glfwInit();

		m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);

	}

	void WindowsWindow::Shutdown()
	{
        // glfwDestroyWindow(m_Window);
        std::cout << "WIndow Destroyed" << std::endl;
	}

	void WindowsWindow::OnUpdate()
	{
        std::cout << "Updating.. " << std::endl;
		// glfwPollEvents();
	}

	void WindowsWindow::SetVSync(bool enabled)
	{

	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}

}
    */
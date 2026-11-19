#include "Platform/RunWindow.h"
#include <iostream>


namespace GalaxyEngine {

    static bool GLFWInitialized = false;

    Window* Window::Create(const WindowProps& props)
    {
        return new RunWindow(props);
    }

	RunWindow::RunWindow(const WindowProps& props)
	{
		std::cout << "Window Started. " << std::endl;
		Init(props);
	}

	RunWindow::~RunWindow()
	{
		Shutdown();
	}

	void RunWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		glfwInit();

		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, props.Title.c_str(), nullptr, nullptr);

		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height){
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			data.Width = width;
			data.Height = height;

			WindowResizeEvent event(width, height);
			data.EventCallback(event);

			std::cout << event.ToString() << std::endl;
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.EventCallback(event);

			std::cout << event.ToString() << std::endl;
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);

					std::cout << event.ToString() << std::endl;

					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);

					std::cout << event.ToString() << std::endl;

					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, true);
					data.EventCallback(event);

					std::cout << event.ToString() << std::endl;

					break;
				}
			}
		});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			KeyTypedEvent event(keycode);
			data.EventCallback(event);

			std::cout << event.ToString() << std::endl;

		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);

					std::cout << event.ToString() << std::endl;

					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);

					std::cout << event.ToString() << std::endl;

					break;
				}
			}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.EventCallback(event);

			std::cout << event.ToString() << std::endl;

		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)xPos, (float)yPos);
			data.EventCallback(event);

			std::cout << event.ToString() << std::endl;

		});
	}

	void RunWindow::Shutdown()
	{
        glfwDestroyWindow(m_Window);
        std::cout << "WIndow Destroyed" << std::endl;
	}

	void RunWindow::OnUpdate()
	{
		glfwPollEvents();
        glfwSwapBuffers(m_Window);
	}

	void RunWindow::SetVSync(bool enabled)
	{

	}

	bool RunWindow::IsVSync() const
	{
		return m_Data.VSync;
	}

}
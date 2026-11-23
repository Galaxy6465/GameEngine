#include "Application/Application.h"
#include "Core/Log.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Application/ApplicationContext.h"

#include "Layers/Main/RenderLayer.h"
#include "Layers/Main/ImGuiOverlay.h"

#include <utility>

int Application::Init()
{   
    if(!glfwInit()){
        APP_ERROR("INITIALIZE::FAILED");
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //! create Main Window
   m_app_Windows = std::make_unique<Window>(Specifications::WindowContext{"Main Window", 800, 600}, nullptr);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        APP_ERROR("Failed to initialize GLAD!");
        return -1;
    }

    APP_INFO("OpenGL Loaded: ", (const char*)glGetString(GL_VERSION));

    //! Window 1
    GLFWwindow* mainWin = m_app_Windows->GetNativeWindow();
    glfwMakeContextCurrent(mainWin);

    auto renderLayer = std::make_unique<MainRenderLayer>();
    float* cubeColor = renderLayer->m_CubeColor;

    m_app_Windows->PushLayer(std::move(renderLayer));

    m_app_Windows->PushOverlay(std::make_unique<MainImGuiOverlay>(
        m_app_Windows->GetNativeWindow(), cubeColor)
    );

    

    m_app_isRunning = true;

    return 0;
}

void Application::Run()
{
    while (m_app_isRunning) {
        glfwPollEvents();

        if(m_app_Windows && m_app_Windows->ShouldClose()) {
            m_app_isRunning = false;
            m_app_Windows.reset();
        } else if(m_app_Windows) {
            glfwMakeContextCurrent(m_app_Windows->GetNativeWindow());

            m_app_Windows->OnUpdate();
            m_app_Windows->OnRender();
        }
    }
}

void Application::Clean()
{
    m_app_Windows.reset();
    glfwTerminate();
}
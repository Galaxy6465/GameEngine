#include "Application/Application.h"
#include "Core/Log.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Layers/Main/RenderLayer.h"
#include "Layers/Main/ImGuiOverlay.h"
#include "Window/windowContext.h"

#include <utility>


//X =========================== Private Functions =================================|

//! Init Window
int Application::InitWindow(){

    if(!glfwInit()){
        APP_ERROR("INITIALIZE::FAILED");
        return -2;
    }

    appWindow = std::make_unique<Window>(
        WindowContext{"Main Window", 800, 600},
        nullptr
    );
    return 0;
}

//! Init API
int Application::InitAPI() { //! OpenGL Currently

    // OpenGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // GLAD For OpenGL Context
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        APP_ERROR("Failed to initialize GLAD!");
        return -3;
    }

    APP_INFO("OpenGL Loaded: ", (const char*)glGetString(GL_VERSION));

    return 0;
}

//! Init Callbacks
void Application::InitCallbacks() 
{

}

//X =========================== Public Functions =================================|

//! Init
int Application::Init()
{
    int result{};

    result = InitWindow();
    if(result < 0) return -1;

    result = InitAPI();
    if(result < 0) return -1;


    //! Window
    GLFWwindow* mainWin = appWindow->GetNativeWindow();
    glfwMakeContextCurrent(mainWin);

    auto renderLayer = std::make_unique<MainRenderLayer>();

    appWindow->PushLayer(std::move(renderLayer));

    appWindow->PushOverlay(std::make_unique<MainImGuiOverlay>(
        appWindow->GetNativeWindow())
    );

    return result;
}


//! Update
void Application::Update()
{
    glfwPollEvents();
    glfwMakeContextCurrent(appWindow->GetNativeWindow());

    appWindow->ShouldClose();

    appWindow->OnUpdate();
}


//! Run
void Application::Run()
{
    while (!CloseApp()) {
        Update();
        appWindow->OnRender();
    }
}

void Application::Clean()
{
    appWindow.reset();
    glfwTerminate();
}
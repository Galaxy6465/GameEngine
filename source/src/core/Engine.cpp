#include "Core/Engine.h"
#include "Debug/Debug.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace {
void RenderWindow(Window& win, float r, float g, float b, float a)
{
    GLFWwindow* native = win.GetWindow();
    if (!native) return;

    glfwMakeContextCurrent(native);

    int fbW = 0, fbH = 0;
    glfwGetFramebufferSize(native, &fbW, &fbH);
    glViewport(0, 0, fbW, fbH);

    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);

    win.OnUpdate();
    glfwSwapBuffers(native);
}
} // namespace

Engine::Engine(const char* title)
{
    ctx.Title = title;
}

Engine::~Engine()
{
    // Destroy FirstWindow while GLFW is still active
    if (FirstWindow) {
        if (FirstWindow->GetWindow()) {
            glfwMakeContextCurrent(FirstWindow->GetWindow());
        }
        FirstWindow.reset();
    }

    for (Window& win : windowList) {
        if (win.GetWindow()) {
            glfwMakeContextCurrent(win.GetWindow());
            glfwDestroyWindow(win.GetWindow());
        }
    }

    windowList.clear();
    glfwTerminate();
}

int Engine::Init(const char* API_Name)
{
    if (!glfwInit()) {
        APP_ERROR("Failed to initialize GLFW");
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    ctx.API = API_Name;
    APP_TRACE("API INITIALIZED : ", API_Name);

    windowList.emplace_back(ctx.Title, 900.0f, 600.0f);
    Window& mainWin = windowList.back();
    mainWin.Init(nullptr);

    if (!mainWin.GetWindow()) {
        APP_ERROR("Failed to create main window");
        glfwTerminate();
        return -1;
    }

    mainWin.CreateContext();

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        APP_ERROR("Failed to initialize GLAD");
        glfwDestroyWindow(mainWin.GetWindow());
        glfwTerminate();
        return -1;
    }

    FirstWindow = std::make_unique<MainWindow>("First Window", 800.0f, 800.0f);
    FirstWindow->Init(mainWin.GetWindow());
    if (FirstWindow->GetWindow()) {
        FirstWindow->CreateContext();
        FirstWindow->Init_OpenGL();
    }

    // Restore main window context after setting up FirstWindow
    glfwMakeContextCurrent(mainWin.GetWindow());

    ctx.Running = true;
    return 0;
}

void Engine::OnUpdate()
{
    if (windowList.empty()) {
        ctx.Running = false;
        return;
    }

    glfwPollEvents();

    GLFWwindow* primaryNativeWindow = windowList[0].GetWindow();
    if (!primaryNativeWindow || glfwWindowShouldClose(primaryNativeWindow)) {
        ctx.Running = false;
        return;
    }

    RenderWindow(windowList[0], 0.1f, 0.1f, 0.15f, 1.0f);

    if (FirstWindow && FirstWindow->GetWindow()) {
        if (glfwWindowShouldClose(FirstWindow->GetWindow())) {
            FirstWindow.reset();
            glfwMakeContextCurrent(primaryNativeWindow);
        } else {
            RenderWindow(*FirstWindow, 0.15f, 0.1f, 0.2f, 1.0f);
        }
    }

    glfwMakeContextCurrent(primaryNativeWindow);
}

void Engine::SetState() {}

void Engine::Run()
{
    while (ctx.Running) {
        OnUpdate();

        FirstWindow->CreateWindow();
    }
}
#pragma once

#include "Window/Window.h"
#include <vector>
#include <memory>

class Application {
public:
    Application() = default;
    ~Application() = default;

    int Init();
    void Run();
    void Clean();

    bool CloseApp() { return glfwWindowShouldClose(appWindow->GetNativeWindow()); }

private:
    int InitWindow();
    int InitAPI();
    void InitCallbacks();

    void Update();

private:
    std::unique_ptr<Window> appWindow;
};
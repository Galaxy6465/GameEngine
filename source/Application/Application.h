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
private:
    bool m_app_isRunning = false;
    std::unique_ptr<Window> m_app_Windows;
    std::unique_ptr<Window> m_app_Windows2;
};
#pragma once

#include <iostream>
#include <functional>
#include <memory>
#include <vector>
#include "window/Window.h"
#include "window/MainWindow.h"

struct EngineContext {
    const char* Title = nullptr;
    bool Running  = true;
    const char* API = nullptr;
};

class Engine {
public:
    using State = std::function<bool(bool)>;

    Engine(const char* title);
    ~Engine();

    int Init(const char* API_Name);
    void OnUpdate();
    void SetState();
    void Run();

public:
    EngineContext ctx;
    std::vector<Window> windowList;
    std::unique_ptr<MainWindow> FirstWindow;
};
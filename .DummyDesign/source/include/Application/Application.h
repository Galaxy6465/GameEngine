#pragma once
#include <memory>
#include "Window/Window.h"
#include "Events/ApplicationEvent.h"
#include "Platform/RunWindow.h"
#include <functional>
#include "Layers/Layer.h"
#include "Layers/LayerStack.h"

namespace GalaxyEngine {

    class Application
    {
    private:
        
    public:
        Application();
        virtual ~Application();

        void Run();

        void OnEvent(Event& event);

        void PushLayer(Layer* layer);

        void PushOverlay(Layer* layer);
    private:
        bool OnWindowClose(WindowCloseEvent& e);

        std::string title;
        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
        LayerStack m_LayerStack;
    };

    Application* CreateApplication();
}
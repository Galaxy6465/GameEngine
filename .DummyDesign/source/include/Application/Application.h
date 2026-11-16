#pragma once

namespace GalaxyEngine {

    class Application
    {
    private:
        
    public:
        Application();
        virtual ~Application();

        void Run();
    };

    Application* CreateApplication();
}